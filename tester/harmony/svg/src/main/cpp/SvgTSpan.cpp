#include "SvgTSpan.h"
#include <native_drawing/drawing_font_collection.h>

#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"

namespace rnoh {

void SvgTSpan::OnDraw(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        InitGlyph(canvas);
    }
    if (content.empty()) {
        for (const auto &child : children_) {
            if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child); tSpan) {
                tSpan->SetContext(glyphCtx_);
            }
        }
        return;
    }
    // if (inlineSize_) {
        DrawWrappedText(canvas);
    // } else {
        /* TODO: draw each character individually */
    // }
}

void SvgTSpan::DrawWrappedText(OH_Drawing_Canvas * canvas) {
    glyphCtx_->pushContext(false, shared_from_this(), {}, x_, y_, dx_, dy_, rotate_);
    UpdateStrokeStyle();
    auto fillOpaque = UpdateFillStyle();
    if (!fillOpaque) {
        OH_Drawing_BrushSetColor(fillBrush_, Color::TRANSPARENT.GetValue());
    }
    drawing::TextStyle textStyle;
    textStyle.SetForegroundBrush(fillBrush_);
    textStyle.SetForegroundPen(strokePen_);
    textStyle.SetFontSize(fontSize);
    drawing::TypographyStyle typographyStyle;
    typographyStyle.SetTextStyle(std::move(textStyle));
    auto fontCollection = OH_Drawing_CreateFontCollection();
    auto typographyHandler = OH_Drawing_CreateTypographyHandler(typographyStyle.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content.c_str());
    auto typography = OH_Drawing_CreateTypography(typographyHandler);
    double maxWidth = inlineSize_.value_or(Infinity<Dimension>()).ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
    OH_Drawing_TypographyLayout(typography, maxWidth);
    double dx = glyphCtx_->nextX(0) + glyphCtx_->nextDeltaX();
    double dy = glyphCtx_->nextY() + glyphCtx_->nextDeltaY();
    LOG(INFO) << "TEXT GLYPH next X = " << dx << " next dy = " << dy;
    OH_Drawing_TypographyPaint(typography, canvas, dx, dy);

    LOG(INFO) << "TEXT GLYPH current size = " << textSize.ToString();
    OH_Drawing_DestroyTypography(typography);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
    OH_Drawing_DestroyFontCollection(fontCollection);

    glyphCtx_->popContext();
}

} // namespace rnoh