#pragma once

#include "SvgGraphic.h"
#include "SvgText.h"
#include <native_drawing/drawing_text_typography.h>
#include "utils/GlyphContext.h"

namespace rnoh {

class SvgTSpan : public SvgGraphic {
public:
    SvgTSpan() = default;
    ~SvgTSpan() override = default;

    /**
     * @param startPos starting position to draw this tSpan.
     * @return End position after drawing this tSpan.
     */
    Offset DrawText(OH_Drawing_Canvas *canvas, Offset startPos);

    void OnDraw(OH_Drawing_Canvas *canvas) override {
        DrawText(canvas, {0, 0});
    }

    void SetParent(std::shared_ptr<SvgGraphic> parent) { parent_ = parent; }
    void SetContext(std::shared_ptr<GlyphContext> context) { context_ = context; }

    std::vector<Dimension> x_;
    std::vector<Dimension> y_;
    std::vector<Dimension> rotate_;
    std::vector<Dimension> dx_;
    std::vector<Dimension> dy_;

    std::string content;
    double fontSize;

private:
    std::shared_ptr<SvgGraphic> parent_;
    std::shared_ptr<GlyphContext> context_;
};

} // namespace rnoh