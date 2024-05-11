#pragma once

#include "SvgGroup.h"
#include <native_drawing/drawing_text_typography.h>

namespace rnoh {

class SvgText : public SvgGroup {
public:
    SvgText() = default;
    ~SvgText() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    std::vector<Dimension> mPositionX;
    std::vector<Dimension> mPositionY;
    std::vector<Dimension> mRotate;
    std::vector<Dimension> mDeltaX;
    std::vector<Dimension> mDeltaY;

    std::string text;
    double fontSize;

private:
    std::shared_ptr<GlyphContext> context_ = std::make_shared<GlyphContext>();
};

} // namespace rnoh