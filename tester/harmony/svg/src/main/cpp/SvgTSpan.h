#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_text_typography.h>

namespace rnoh {

class SvgTSpan : public SvgGraphic {
public:
    SvgTSpan() = default;
    ~SvgTSpan() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    std::vector<double> x;
    std::vector<double> y;
    std::string content;
    double fontSize;

private:
};

} // namespace rnoh