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

    UpdateStrokeStyle();
    auto fillOpaque = UpdateFillStyle();
    if (!fillOpaque) {
        OH_Drawing_BrushSetColor(fillBrush_, Color::TRANSPARENT.GetValue());
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
    drawing::TextStyle textStyle;
    textStyle.SetForegroundBrush(fillBrush_);
    textStyle.SetForegroundPen(strokePen_);
    textStyle.Update(font_);
    drawing::TypographyStyle ts;
    ts.SetTextStyle(std::move(textStyle));
    ts.Update(font_);
    auto *fontCollection = OH_Drawing_CreateFontCollection();
    LOG(INFO) << "TS = " << ts.typographyStyle_.get();
    auto *typographyHandler = OH_Drawing_CreateTypographyHandler(ts.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content_.c_str());
    auto typography = OH_Drawing_CreateTypography(typographyHandler);
    double maxWidth = inlineSize_.value_or(Infinity<Dimension>()).ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
    LOG(INFO) << "TEXT GLYPH maxWidth = " << maxWidth;
    OH_Drawing_TypographyLayout(typography, maxWidth);
    double dx = glyphCtx_->nextX(0) + glyphCtx_->nextDeltaX();
    double dy = glyphCtx_->nextY() + glyphCtx_->nextDeltaY();
    LOG(INFO) << "TEXT GLYPH next X = " << dx << " next dy = " << dy;
    OH_Drawing_TypographyPaint(typography, canvas, dx, dy);

    //     LOG(INFO) << "TEXT GLYPH current size = " << textSize.ToString();
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

void SvgTSpan::DrawOnPath(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "TEXT_PATH DRAW content = " << content_;
    if (content_.empty()) {
        return;
    }

    OH_Drawing_Path *path = textPath_ ? textPath_->getTextPath() : nullptr;
    double pathLength = OH_Drawing_PathGetLength(path, false);
    if (pathLength == 0) {
        return;
    }
    bool isClosed = OH_Drawing_PathIsClosed(path, false);
    LOG(INFO) << "TEXT_PATH pathLen = " << pathLength;

    // TODO TextAnchor
    TextAnchor textAnchor = font_->textAnchor;
    double textMeasure = 0;
    double offset = getTextAnchorOffset(textAnchor, textMeasure);

    double startOfRendering = 0;
    double endOfRendering = pathLength;
    bool sharpMidLine = textPath_->getMidLine() == TextPathMidLine::sharp;
    int side = textPath_->getSide() == TextPathSide::right ? -1 : 1;
    double absoluteStartOffset = textPath_->getStartOffset();
    offset += absoluteStartOffset;
    if (isClosed) {
        startOfRendering = absoluteStartOffset + (textAnchor == TextAnchor::middle ? -pathLength / 2.0 : 0);
        endOfRendering = startOfRendering + pathLength;
    }

    double scaleSpacingAndGlyphs = 1.0;
    double scaledDirection = scaleSpacingAndGlyphs * side;

    drawing::TextStyle textStyle;
    textStyle.SetForegroundBrush(fillBrush_);
    textStyle.SetForegroundPen(strokePen_);
    textStyle.Update(font_);
    drawing::TypographyStyle ts;
    ts.SetTextStyle(std::move(textStyle));
    ts.Update(font_);
    auto *fontCollection = OH_Drawing_CreateFontCollection();
    auto *typographyHandler = OH_Drawing_CreateTypographyHandler(ts.typographyStyle_.get(), fontCollection);
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