#pragma once

#include "SvgGraphic.h"
#include "SvgText.h"
#include <native_drawing/drawing_text_typography.h>
#include "utils/GlyphContext.h"
#include "properties/Font.h"

namespace rnoh {

class SvgTextPath : public SvgGraphic, public SvgText {
public:
    SvgTextPath() {
        hrefFill_ = true;
        hrefRender_ = true;
        passStyle_ = true;
        inheritStyle_ = true;
        drawTraversed_ = true;
    }
    ~SvgTextPath() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    void SetContext(std::shared_ptr<GlyphContext> context) { glyphCtx_ = context; }

    OH_Drawing_Path *getTextPath();

    TextPathMidLine getMidLine() { return midLine_; }

    TextPathSide getSide() { return side_; }

    double getStartOffset() { return startOffset_; }

    TextPathSide side_;
    TextPathMidLine midLine_;
    TextPathMethod method_{TextPathMethod::align};
    TextPathSpacing spacing_{TextPathSpacing::Exact};
    double startOffset_;
    std::string href_;

private:
};

} // namespace rnoh