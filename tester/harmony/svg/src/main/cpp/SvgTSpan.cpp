#include <native_drawing/drawing_font_collection.h>
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_text_blob.h>
#include "SvgTSpan.h"
#include "drawing/TextStyle.h"
#include "properties/Offset.h"
#include "drawing/Matrix.h"

namespace rnoh {
namespace {
constexpr int MSCALE_X = 0; //!< use with getValues/setValues
constexpr int MSKEW_X = 1;  //!< use with getValues/setValues
constexpr int MTRANS_X = 2; //!< use with getValues/setValues
constexpr int MSKEW_Y = 3;  //!< use with getValues/setValues
constexpr int MSCALE_Y = 4; //!< use with getValues/setValues
constexpr int MTRANS_Y = 5; //!< use with getValues/setValues
constexpr int MPERSP_0 = 6; //!< use with getValues/setValues
constexpr int MPERSP_1 = 7; //!< use with getValues/setValues
constexpr int MPERSP_2 = 8; //!< use with getValues/setValues

constexpr double tau = 2.0 * M_PI;
constexpr double radToDeg = 360.0 / tau;
} // namespace

void SvgTSpan::OnDraw(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        InitGlyph(canvas);
    }
    if (content_.empty()) {
        for (const auto &child : children_) {
            if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child); tSpan) {
                tSpan->SetContext(glyphCtx_);
            }
        }
        return;
    }


    glyphCtx_->pushContext(false, shared_from_this(), x_, y_, dx_, dy_, rotate_);
    if (!textPath_) {
        DrawText(canvas);
    } else {
        DrawOnPath(canvas);
    }
    glyphCtx_->popContext();
}

void SvgTSpan::DrawText(OH_Drawing_Canvas *canvas) {
    drawing::TypographyStyle ts = PrepareTypoStyle();
    auto *fontCollection = OH_Drawing_CreateFontCollection();
    auto *typographyHandler = OH_Drawing_CreateTypographyHandler(ts.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content_.c_str());
    auto *typography = OH_Drawing_CreateTypography(typographyHandler);
    double maxWidth = inlineSize_.value_or(Infinity<Dimension>()).ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
    OH_Drawing_TypographyLayout(typography, maxWidth);
    double actualWidth = OH_Drawing_TypographyGetLongestLine(typography);
    LOG(INFO) << "TEXT GLYPH maxWidth = " << maxWidth << " ACTUAL width = " << actualWidth;
    double dx = glyphCtx_->nextX(actualWidth) - actualWidth + glyphCtx_->nextDeltaX();
    double dy = glyphCtx_->nextY() + glyphCtx_->nextDeltaY();
    LOG(INFO) << "TEXT GLYPH next X = " << dx << " next dy = " << dy;

    double r = glyphCtx_->nextRotation();
    drawing::Matrix mat;
    OH_Drawing_MatrixPreRotate(&mat, r, dx, dy);

    OH_Drawing_CanvasSave(canvas);
    OH_Drawing_CanvasConcatMatrix(canvas, &mat);
    OH_Drawing_TypographyPaint(typography, canvas, dx, dy);
    OH_Drawing_CanvasRestore(canvas);

    OH_Drawing_DestroyTypography(typography);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
    OH_Drawing_DestroyFontCollection(fontCollection);
}

double SvgTSpan::getTextAnchorOffset(TextAnchor textAnchor, const double &textMeasure) {
    switch (textAnchor) {
    default:
    case TextAnchor::start:
        return 0;

    case TextAnchor::middle:
        return -textMeasure / 2;

    case TextAnchor::end:
        return -textMeasure;
    }
}

drawing::TypographyStyle SvgTSpan::PrepareTypoStyle() {
    UpdateStrokeStyle();
    auto fillOpaque = UpdateFillStyle();
    if (!fillOpaque) {
        OH_Drawing_BrushSetColor(fillBrush_, Color::TRANSPARENT.GetValue());
    }

    drawing::TextStyle textStyle;
    textStyle.SetForegroundBrush(fillBrush_);
    textStyle.SetForegroundPen(strokePen_);
    textStyle.Update(font_);
    drawing::TypographyStyle ts;
    ts.SetTextStyle(std::move(textStyle));
    ts.Update(font_);
    return std::move(ts);
}

void SvgTSpan::DrawOnPath(OH_Drawing_Canvas *canvas) {
    if (content_.empty()) {
        return;
    }

    OH_Drawing_Path *path = textPath_ ? textPath_->getTextPath() : nullptr;
    double pathLength = OH_Drawing_PathGetLength(path, false);
    if (pathLength == 0) {
        return;
    }
    bool isClosed = OH_Drawing_PathIsClosed(path, false);

    drawing::TypographyStyle ts = PrepareTypoStyle();
    auto *fontCollection = OH_Drawing_CreateFontCollection();
    auto *typographyHandler = OH_Drawing_CreateTypographyHandler(ts.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content_.c_str());
    auto *typography = OH_Drawing_CreateTypography(typographyHandler);
    OH_Drawing_TypographyLayout(typography, 1e9);
    double textMeasure = OH_Drawing_TypographyGetLineWidth(typography, 0);
    double offset = getTextAnchorOffset(font_->textAnchor, textMeasure);

    double startOfRendering = 0;
    double endOfRendering = pathLength;
    bool sharpMidLine = textPath_->getMidLine() == TextPathMidLine::sharp;
    int side = textPath_->getSide() == TextPathSide::right ? -1 : 1;
    double absoluteStartOffset = textPath_->getStartOffset();
    offset += absoluteStartOffset;
    if (isClosed) {
        startOfRendering = absoluteStartOffset + (font_->textAnchor == TextAnchor::middle ? -pathLength / 2.0 : 0);
        endOfRendering = startOfRendering + pathLength;
    }

    double scaleSpacingAndGlyphs = 1.0;
    if (textLength_) {
        double author = textLength_->ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
        switch (lengthAdjust_) {
        default:
        case TextLengthAdjust::spacing:
            font_->letterSpacing += (author - textMeasure) / (content_.size() - 1);
            break;
        case TextLengthAdjust::spacingAndGlyphs:
            scaleSpacingAndGlyphs = author / textMeasure;
            break;
        }
    }
    double scaledDirection = scaleSpacingAndGlyphs * side;

    OH_Drawing_Font_Metrics fm;
    bool res = OH_Drawing_TextStyleGetFontMetrics(typography, ts.textStyle_.textStyle_.get(), &fm);
    LOG(INFO) << "GET FONT METRICS = " << res;
    const double descenderDepth = fm.descent;
    const double bottom = descenderDepth + fm.leading;
    const double ascenderHeight = -fm.ascent + fm.leading;
    const double top = -fm.top;
    const double totalHeight = top + bottom;
    double baselineShift = 0;
    switch (align_) {
    // https://wiki.apache.org/xmlgraphics-fop/LineLayout/AlignmentHandling
    default:
    case AlignmentBaseline::baseline:
        // Use the dominant baseline choice of the parent.
        // Match the box’s corresponding baseline to that of its parent.
        baselineShift = 0;
        break;

    case AlignmentBaseline::textBottom:
    case AlignmentBaseline::afterEdge:
    case AlignmentBaseline::textAfterEdge:
        // Match the bottom of the box to the bottom of the parent’s content area.
        // text-after-edge = text-bottom
        // text-after-edge = descender depth
        baselineShift = -descenderDepth;
        break;

    case AlignmentBaseline::alphabetic:
        // Match the box’s alphabetic baseline to that of its parent.
        // alphabetic = 0
        baselineShift = 0;
        break;

    case AlignmentBaseline::ideographic:
        baselineShift = -descenderDepth;
        break;

    case AlignmentBaseline::middle: {
        // Rect bounds;
        // paint.getTextBounds("x", 0, 1, &bounds);
        // int xHeight = bounds.height();
        // baselineShift = xHeight / 2.0;
        break;
    }
    case AlignmentBaseline::central:
        baselineShift = (ascenderHeight - descenderDepth) / 2;
        break;

    case AlignmentBaseline::mathematical:
        baselineShift = 0.5 * ascenderHeight;
        break;

    case AlignmentBaseline::hanging:
        baselineShift = 0.8 * ascenderHeight;
        break;

    case AlignmentBaseline::textTop:
    case AlignmentBaseline::beforeEdge:
    case AlignmentBaseline::textBeforeEdge:
        baselineShift = ascenderHeight;
        break;

    case AlignmentBaseline::bottom:
        baselineShift = bottom;
        break;

    case AlignmentBaseline::center:
        baselineShift = totalHeight / 2;
        break;

    case AlignmentBaseline::top:
        baselineShift = top;
        break;
    }

    if (!baselineShift_.empty()) {
        switch (align_) {
        case AlignmentBaseline::top:
        case AlignmentBaseline::bottom:
            break;

        default: 
            break;
//             if (baselineShift_ != "sub" && baseline ) {
//             case "sub":
//                 // TODO
//                 break;
//             case "super":
//                 // TODO
//                 break;
//             case "baseline":
//                 break;
//             default:
//                 baselineShift -= StringUtils::FromString(baselineShift_).ConvertToPx(scale_ * fontSize);
//             }
//             break;
//                 }
        }
    }

    for (int i = 0; i < content_.size(); i++) {
        std::string current = content_.substr(i, 1);

        OH_Drawing_TypographyHandlerAddText(typographyHandler, current.c_str());
        auto *typography = OH_Drawing_CreateTypography(typographyHandler);
        OH_Drawing_TypographyLayout(typography, 1e9);
        double charWidth = OH_Drawing_TypographyGetLineWidth(typography, 0);

        bool alreadyRenderedGraphemeCluster = false;
        bool hasLigature = false;

        bool isWordSeparator = current[0] == ' ';
        double wordSpace = isWordSeparator ? font_->wordSpacing : 0;
        double spacing = wordSpace + font_->letterSpacing;
        double advance = charWidth + spacing;

        double x = glyphCtx_->nextX(alreadyRenderedGraphemeCluster ? 0 : advance);
        double y = glyphCtx_->nextY();
        double dx = glyphCtx_->nextDeltaX();
        double dy = glyphCtx_->nextDeltaY();
        double r = glyphCtx_->nextRotation();

        advance *= side;
        charWidth *= side;
        double cursor = offset + (x + dx) * side;
        double startPoint = cursor - advance;

        drawing::Matrix mid;
        const double endPoint = startPoint + charWidth;
        const double halfWay = charWidth / 2;
        const double midPoint = startPoint + halfWay;
        if (midPoint > endOfRendering) {
            continue;
        } else if (midPoint < startOfRendering) {
            continue;
        }
        if (sharpMidLine) {
            OH_Drawing_PathGetMatrix(path, false, midPoint, &mid, GET_POSITION_AND_TANGENT_MATRIX);
        } else {
            drawing::Matrix start;
            drawing::Matrix end;
            if (startPoint < 0) {
                OH_Drawing_PathGetMatrix(path, false, startPoint, &start, GET_POSITION_AND_TANGENT_MATRIX);
                OH_Drawing_MatrixPreTranslate(&start, startPoint, 0);
            } else {
                OH_Drawing_PathGetMatrix(path, false, startPoint, &start, GET_POSITION_MATRIX);
            }
            OH_Drawing_PathGetMatrix(path, true, midPoint, &mid, GET_POSITION_MATRIX);

            if (endPoint > pathLength) {
                OH_Drawing_PathGetMatrix(path, false, pathLength, &end, GET_POSITION_AND_TANGENT_MATRIX);
                OH_Drawing_MatrixPreTranslate(&end, (endPoint - pathLength), 0);
            } else {
                OH_Drawing_PathGetMatrix(path, false, endPoint, &end, GET_POSITION_MATRIX);
            }

            double startX = OH_Drawing_MatrixGetValue(&start, MTRANS_X);
            double startY = OH_Drawing_MatrixGetValue(&start, MTRANS_Y);
            double endX = OH_Drawing_MatrixGetValue(&end, MTRANS_X);
            double endY = OH_Drawing_MatrixGetValue(&end, MTRANS_Y);

            double lineX = endX - startX;
            double lineY = endY - startY;

            double glyphMidlineAngle = std::atan2(lineY, lineX);
            OH_Drawing_MatrixPreRotate(&mid, (glyphMidlineAngle * radToDeg * side), 0, 0);
        }

        OH_Drawing_MatrixPreTranslate(&mid, -halfWay, dy);
        OH_Drawing_MatrixPreScale(&mid, scaledDirection, side, 0, 0);
        OH_Drawing_MatrixPostTranslate(&mid, 0, y);
        OH_Drawing_MatrixPreRotate(&mid, r, 0, 0);
        OH_Drawing_CanvasSave(canvas);
        OH_Drawing_CanvasConcatMatrix(canvas, &mid);

        OH_Drawing_TypographyPaint(typography, canvas, 0, 0);
        OH_Drawing_CanvasRestore(canvas);

        OH_Drawing_DestroyTypography(typography);
    }
    OH_Drawing_DestroyFontCollection(fontCollection);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
}

} // namespace rnoh