#include "SvgTSpan.h"
#include <native_drawing/drawing_font_collection.h>

#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"

namespace rnoh {

Offset SvgTSpan::DrawText(OH_Drawing_Canvas *canvas, Offset startPos) {

    if (content.empty()) {
        for (const auto &child : children_) {
            if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child); tSpan) {
                startPos = tSpan->DrawText(canvas, startPos);
            }
        }
        return startPos;
    }

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
    OH_Drawing_TypographyLayout(typography, 1e9);
    OH_Drawing_TypographyPaint(typography, canvas, x[0], y[0]);

    Size textSize = {OH_Drawing_TypographyGetMaxWidth(typography), OH_Drawing_TypographyGetHeight(typography)};

    LOG(INFO) << "current pos = " << textSize.ToString();
    OH_Drawing_DestroyTypography(typography);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
    OH_Drawing_DestroyFontCollection(fontCollection);

    return startPos;
}

} // namespace rnoh