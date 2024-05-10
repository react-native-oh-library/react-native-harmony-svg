#include "TextStyle.h"

namespace drawing {

drawing::TextStyle::TextStyle() : textStyle_(UniqueTextStyle(OH_Drawing_CreateTextStyle(), OH_Drawing_DestroyTextStyle))
{
}

} // namespace drawing