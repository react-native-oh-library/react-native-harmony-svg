#pragma once

#include <memory>
#include <native_drawing/drawing_text_typography.h>
#include "properties/Font.h"

namespace rnoh::drawing {

class TextStyle final {

using UniqueTextStyle = std::unique_ptr<OH_Drawing_TextStyle, decltype(&OH_Drawing_DestroyTextStyle)>;
public:
    TextStyle();
    ~TextStyle() noexcept = default;

    TextStyle(const TextStyle &) = delete;
    TextStyle &operator=(const TextStyle &) = delete;

    TextStyle(TextStyle &&) = default;
    TextStyle &operator=(TextStyle &&) = default;

    void SetForegroundPen(OH_Drawing_Pen *pen) {
        OH_Drawing_SetTextStyleForegroundPen(textStyle_.get(), pen);
    }

    void SetForegroundBrush(OH_Drawing_Brush *brush) {
        OH_Drawing_SetTextStyleForegroundBrush(textStyle_.get(), brush);
    }

    void Update(const std::shared_ptr<FontData>& style);
// private:
     UniqueTextStyle textStyle_;
     friend class TypographyStyle;
};

} // namespace rnoh::drawing