#pragma once

#include "SvgGraphic.h"
#include "SvgText.h"
#include <native_drawing/drawing_text_typography.h>
#include "utils/GlyphContext.h"

namespace rnoh {

class SvgTSpan : public SvgGraphic, public SvgText {
public:
    SvgTSpan() {
        hrefFill_ = true;
        hrefRender_ = true;
        passStyle_ = true;
        inheritStyle_ = true;
        drawTraversed_ = true;
    }
    ~SvgTSpan() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    void SetParent(std::shared_ptr<SvgNode> parent) { parent_ = parent; }
    void SetContext(std::shared_ptr<GlyphContext> context) { glyphCtx_ = context; }

    std::string content;

private:
    void DrawWrappedText(OH_Drawing_Canvas* canvas);
    std::shared_ptr<SvgNode> parent_;
};

} // namespace rnoh