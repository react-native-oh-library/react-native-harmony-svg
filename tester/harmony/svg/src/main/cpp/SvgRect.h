#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_rect.h>
#include <native_drawing/drawing_round_rect.h>

namespace rnoh {
namespace svg {

class SvgRect : public SvgGraphic {
public:
    using Float = facebook::react::Float;
    SvgRect() = default;
    ~SvgRect() override = default;
    Float x;
    Float y;
    Float width;
    Float height;
    Float rx;
    Float ry;
    
    OH_Drawing_Path *AsPath() override;
};

} // namespace svg
} // namespace rnoh