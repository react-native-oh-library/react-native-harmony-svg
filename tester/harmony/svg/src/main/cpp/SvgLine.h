#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_rect.h>

namespace rnoh {
namespace svg {

class SvgLine : public SvgGraphic {
public:
    using Float = facebook::react::Float;
    SvgLine() = default;
    ~SvgLine() override = default;
    Float x1;
    Float y1;
    Float x2;
    Float y2;

    OH_Drawing_Path *AsPath() override;
};

} // namespace svg
} // namespace rnoh