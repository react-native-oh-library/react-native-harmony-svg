#include "TypographyStyle.h"
#include <native_drawing/drawing_text_typography.h>

namespace rnoh::drawing {

TypographyStyle::TypographyStyle()
    : typographyStyle_(UniqueTypographyStyle(OH_Drawing_CreateTypographyStyle(), OH_Drawing_DestroyTypographyStyle)) {}

TypographyStyle::~TypographyStyle() noexcept {}

void TypographyStyle::SetTextStyle(TextStyle textStyle) {
    textStyle_ = std::move(textStyle.textStyle_);
    OH_Drawing_SetTypographyTextStyle(typographyStyle_.get(), textStyle_.get());
}

void TypographyStyle::Update(const std::shared_ptr<svg::FontData> &style) {
    auto* ts = typographyStyle_.get();
    OH_Drawing_SetTypographyTextFontWeight(ts, style->absoluteFontWeight);
    OH_Drawing_SetTypographyTextFontStyle(ts, static_cast<int>(style->fontStyle));
    OH_Drawing_SetTypographyTextFontFamily(ts, style->fontFamily.c_str());
    OH_Drawing_SetTypographyTextFontSize(ts, style->fontSize);
    OH_Drawing_SetTypographyTextAlign(ts, static_cast<int>(style->textAnchor));
}

} // namespace rnoh::drawing
