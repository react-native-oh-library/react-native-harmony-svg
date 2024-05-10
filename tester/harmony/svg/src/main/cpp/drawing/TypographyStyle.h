#pragma once

#include <memory>
#include <optional>
#include <native_drawing/drawing_text_typography.h>

#include "TextStyle.h"

namespace drawing {

class TypographyStyle final {

using UniqueTypographyStyle = std::unique_ptr<OH_Drawing_TypographyStyle, decltype(&OH_Drawing_DestroyTypographyStyle)>;
public:
    TypographyStyle();
    ~TypographyStyle() noexcept;

    void SetTextStyle(TextStyle textStyle);

    void SetFontSize(double fontSize);

// private:
     UniqueTypographyStyle typographyStyle_;
     std::optional<TextStyle> textStyle_;
};

} // namespace drawing