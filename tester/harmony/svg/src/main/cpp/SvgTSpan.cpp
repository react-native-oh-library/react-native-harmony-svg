#include <native_drawing/drawing_font_collection.h>
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_text_blob.h>
#include <vector>
#include "SvgTSpan.h"
#include "drawing/TextStyle.h"
#include "properties/Offset.h"
#include "drawing/Typography.h"
#include "drawing/Matrix.h"
#include "utils/TextPathHelper.h"

namespace rnoh {

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
        DrawWrappedText(canvas);
    } else {
        // TODO: draw tSpan with this function
        DrawText(canvas);
    }
    glyphCtx_->popContext();
}

void SvgTSpan::DrawWrappedText(OH_Drawing_Canvas *canvas) {
    drawing::TypographyStyle ts = PrepareTypoStyle();
    auto *fontCollection = OH_Drawing_CreateFontCollection();
    auto *typographyHandler = OH_Drawing_CreateTypographyHandler(ts.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content_.c_str());
    auto *typography = OH_Drawing_CreateTypography(typographyHandler);
    double maxWidth = inlineSize_.value_or(Infinity<Dimension>()).ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
    OH_Drawing_TypographyLayout(typography, maxWidth);
    double actualWidth = OH_Drawing_TypographyGetLongestLine(typography);

    double scaleSpacingAndGlyphs = 1.0;
    if (AdjustSpacing(canvas, actualWidth, scaleSpacingAndGlyphs)) {
        OH_Drawing_SetTextStyleLetterSpacing(ts.textStyle_.get(), font_->letterSpacing);
    }


    OH_Drawing_Font_Metrics fm;
    OH_Drawing_TextStyleGetFontMetrics(typography, ts.textStyle_.get(), &fm);
    double dx = glyphCtx_->nextX(actualWidth) - actualWidth + glyphCtx_->nextDeltaX();
    double dy =
        glyphCtx_->nextY() + glyphCtx_->nextDeltaY() + CalcBaselineShift(typographyHandler, ts.textStyle_.get(), fm);
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

bool SvgTSpan::AdjustSpacing(OH_Drawing_Canvas *canvas, double textMeasure, double &scaleSpacingAndGlyphs) {
    if (textLength_) {
        double author = textLength_->ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
        switch (lengthAdjust_) {
        default:
        case TextLengthAdjust::spacing:
            font_->letterSpacing += (author - textMeasure) / (content_.size() - 1);
            return true;
        case TextLengthAdjust::spacingAndGlyphs:
            scaleSpacingAndGlyphs = author / textMeasure;
            break;
        }
    }
    return false;
}

void SvgTSpan::DrawText(OH_Drawing_Canvas *canvas) {
    if (content_.empty()) {
        return;
    }

    TextPathHelper ph(textPath_, font_->textAnchor);
    if (textPath_ && !ph.Valid()) {
        return;
    }

    drawing::TypographyStyle ts = PrepareTypoStyle();
    auto *fontCollection = OH_Drawing_CreateFontCollection();
    auto *typographyHandler = OH_Drawing_CreateTypographyHandler(ts.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content_.c_str());
    auto *typography = OH_Drawing_CreateTypography(typographyHandler);
    OH_Drawing_TypographyLayout(typography, 1e9);
    double textMeasure = OH_Drawing_TypographyGetLineWidth(typography, 0);
    double offset = getTextAnchorOffset(font_->textAnchor, textMeasure);

    offset += ph.GetStartOffset();

    double scaleSpacingAndGlyphs = 1.0;
    if (AdjustSpacing(canvas, textMeasure, scaleSpacingAndGlyphs)) {
        OH_Drawing_SetTextStyleLetterSpacing(ts.textStyle_.get(), font_->letterSpacing);
    }
    ph.SetScaleSpacingAndGlyphs(scaleSpacingAndGlyphs);

    std::vector<bool> ligature(content_.size(), false);

    OH_Drawing_Font_Metrics fm;
    OH_Drawing_TextStyleGetFontMetrics(typography, ts.textStyle_.get(), &fm);
    double baselineShift = CalcBaselineShift(typographyHandler, ts.textStyle_.get(), fm);

    for (int i = 0; i < content_.size(); i++) {
        std::string current = content_.substr(i, 1);

        OH_Drawing_TypographyHandlerAddText(typographyHandler, current.c_str());
        drawing::Typography typography(typographyHandler);
        OH_Drawing_TypographyLayout(&typography, 1e9);
        double charWidth = OH_Drawing_TypographyGetLineWidth(&typography, 0);

        bool alreadyRenderedGraphemeCluster = false;
        bool hasLigature = false;

        if (alreadyRenderedGraphemeCluster) {
            current = "";
        } else {
            int nextIndex = i;
            while (++nextIndex < content_.size()) {
                float nextWidth = charWidth;
                if (nextWidth > 0) {
                    break;
                }
                std::string nextLigature = current + current[nextIndex];
                ligature[nextIndex] = true;
                current = nextLigature;
                hasLigature = true;
            }
        }
        bool autoKerning = !font_->manualKerning;
        double kerning = font_->kerning;
        if (autoKerning) {
            double kerned = charWidth * scaleSpacingAndGlyphs;
            kerning = kerned - charWidth;
        }

        bool isWordSeparator = current[0] == ' ';
        double wordSpace = isWordSeparator ? font_->wordSpacing : 0;
        double spacing = wordSpace + font_->letterSpacing;
        double advance = charWidth + spacing;

        double x = glyphCtx_->nextX(alreadyRenderedGraphemeCluster ? 0 : kerning + advance);
        double y = glyphCtx_->nextY();
        double dx = glyphCtx_->nextDeltaX();
        double dy = glyphCtx_->nextDeltaY();
        double r = glyphCtx_->nextRotation();

        if (alreadyRenderedGraphemeCluster || isWordSeparator) {
            // Skip rendering other grapheme clusters of ligatures (already rendered),
            // But, make sure to increment index positions by making gc.next() calls.
            continue;
        }
        int side = textPath_ ? ph.GetSide() : 1;
        advance *= side;
        charWidth *= side;
        double cursor = offset + (x + dx) * side;
        double startPoint = cursor - advance;

        drawing::Matrix mid;
        if (textPath_) {
            if (!ph.GetMatrixOnPath({charWidth, startPoint, y, dy + baselineShift}, mid)) {
                continue;
            }
        } else {
            LOG(INFO) << "paint text " << current << " x = " << x << " y = " << y << " dx = " << dx << " dy = " << dy
                      << " r = " << r << " baselineShift = " << baselineShift;
            OH_Drawing_MatrixTranslate(&mid, startPoint, y + dy + baselineShift);
        }
        OH_Drawing_MatrixPreRotate(&mid, r, 0, 0);

        OH_Drawing_CanvasSave(canvas);
        OH_Drawing_CanvasConcatMatrix(canvas, &mid);
        OH_Drawing_TypographyPaint(&typography, canvas, 0, 0);
        OH_Drawing_CanvasRestore(canvas);
    }
    OH_Drawing_DestroyFontCollection(fontCollection);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
}

double SvgTSpan::CalcBaselineShift(OH_Drawing_TypographyCreate *handler, OH_Drawing_TextStyle *style,
                                   const OH_Drawing_Font_Metrics &fm) {
    const double descenderDepth = fm.descent;
    const double bottom = descenderDepth + fm.leading;
    const double ascenderHeight = -fm.ascent + fm.leading;
    const double top = -fm.top;
    const double totalHeight = top + bottom;
    double baselineShift = 0.0;
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
        OH_Drawing_TypographyHandlerAddText(handler, "x");
        drawing::Typography typography(handler);
        OH_Drawing_TypographyLayout(&typography, 1e9);
        double xHeight = OH_Drawing_TypographyGetHeight(&typography);
        baselineShift = xHeight / 2.0;
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

        default: {
            if (baselineShift_ == "sub") {
            } else if (baselineShift_ == "super") {
            } else if (baselineShift_ == "baseline") {
            } else {
                baselineShift -= StringUtils::FromString(baselineShift_).ConvertToPx(scale_ * font_->fontSize);
            }
            break;
        }
        }
    }
    return baselineShift;
}
} // namespace rnoh