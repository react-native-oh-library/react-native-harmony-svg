#include "TextStyle.h"

namespace rnoh::drawing {

TextStyle::TextStyle() : textStyle_(UniqueTextStyle(OH_Drawing_CreateTextStyle(), OH_Drawing_DestroyTextStyle)) {}

void TextStyle::Update(const std::shared_ptr<FontData> &style) {
    OH_Drawing_SetTextStyleFontSize(textStyle_.get(), style->fontSize);
    OH_Drawing_SetTextStyleDecoration(textStyle_.get(), static_cast<int>(style->textDecoration));
    OH_Drawing_SetTextStyleLetterSpacing(textStyle_.get(), style->letterSpacing);
    OH_Drawing_SetTextStyleWordSpacing(textStyle_.get(), style->wordSpacing);
}

} // namespace rnoh::drawing