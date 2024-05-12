#include "TypographyStyle.h"
#include <native_drawing/drawing_text_typography.h>

namespace rnoh::drawing {

TypographyStyle::TypographyStyle()
    : typographyStyle_(UniqueTypographyStyle(OH_Drawing_CreateTypographyStyle(), OH_Drawing_DestroyTypographyStyle)) {}

TypographyStyle::~TypographyStyle() noexcept {}

void TypographyStyle::SetTextStyle(TextStyle textStyle) {
    textStyle_ = std::move(textStyle);
    OH_Drawing_SetTypographyTextStyle(typographyStyle_.get(), textStyle_->textStyle_.get());
}

void TypographyStyle::Update(const std::shared_ptr<FontData> &style) {
    OH_Drawing_SetTypographyTextFontWeight(typographyStyle_.get(), static_cast<int>(style->fontWeight));
    OH_Drawing_SetTypographyTextFontStyle(typographyStyle_.get(), static_cast<int>(style->fontStyle));
    OH_Drawing_SetTypographyTextFontFamily(typographyStyle_.get(), style->fontFamily.c_str());
    OH_Drawing_SetTypographyTextFontSize(typographyStyle_.get(), style->fontSize);
}

} // namespace rnoh::drawing
