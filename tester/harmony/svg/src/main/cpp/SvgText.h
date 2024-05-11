#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_text_typography.h>

namespace rnoh {

class SvgText : public SvgGraphic {
public:
    SvgText() = default;
    ~SvgText() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    std::vector<double> x;
    std::vector<double> y;
    double dx;
    double dy;
    std::string text;
    double fontSize;

private:
};

} // namespace rnoh