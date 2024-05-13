#pragma once

#include <memory>
#include <optional>
#include <native_drawing/drawing_text_typography.h>

#include "TextStyle.h"
#include "properties/Font.h"

namespace rnoh::drawing {

class TypographyStyle final {

    using UniqueTypographyStyle =
        std::unique_ptr<OH_Drawing_TypographyStyle, decltype(&OH_Drawing_DestroyTypographyStyle)>;

public:
    TypographyStyle();
    ~TypographyStyle() noexcept;

    // can't move textStyle
    TypographyStyle(TypographyStyle &&other) = delete;
    TypographyStyle &operator=(TypographyStyle && other) = delete;

    void SetTextStyle(TextStyle textStyle);

    void Update(const std::shared_ptr<FontData> &style);

    // private:
    UniqueTypographyStyle typographyStyle_;
    std::optional<TextStyle> textStyle_;
};

} // namespace rnoh::drawing