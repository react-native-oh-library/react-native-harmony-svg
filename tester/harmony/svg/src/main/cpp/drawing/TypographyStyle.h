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

    TypographyStyle(const TypographyStyle &) = delete;
    TypographyStyle &operator=(const TypographyStyle &) = delete;

    TypographyStyle(TypographyStyle &&other) = default;
    TypographyStyle &operator=(TypographyStyle && other) = default;

    void SetTextStyle(TextStyle textStyle);

    void Update(const std::shared_ptr<FontData> &style);

    // private:
    UniqueTypographyStyle typographyStyle_;
    TextStyle::UniqueTextStyle textStyle_ = nullptr;
};

} // namespace rnoh::drawing