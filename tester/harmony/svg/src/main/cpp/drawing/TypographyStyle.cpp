#include "TypographyStyle.h"

namespace drawing {

TypographyStyle::TypographyStyle()
    : typographyStyle_(UniqueTypographyStyle(OH_Drawing_CreateTypographyStyle(), OH_Drawing_DestroyTypographyStyle)) {}

TypographyStyle::~TypographyStyle() noexcept {}

void TypographyStyle::SetTextStyle(TextStyle textStyle)
{
    textStyle_ = std::move(textStyle);
    OH_Drawing_SetTypographyTextStyle(typographyStyle_.get(), textStyle_->textStyle_.get());
}

void TypographyStyle::SetFontSize(double fontSize) {
    OH_Drawing_SetTypographyTextFontSize(typographyStyle_.get(), fontSize);
}

} // namespace drawing
