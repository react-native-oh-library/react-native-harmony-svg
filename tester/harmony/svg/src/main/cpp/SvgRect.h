#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_rect.h>
#include <native_drawing/drawing_round_rect.h>

namespace rnoh {

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
    
    
    OH_Drawing_Path *AsPath() override {
        LOG(INFO) << "[SvgRect] AsPath";
        //TODO implement ConvertDimensionToPx
        auto rect = OH_Drawing_RectCreate(vpToPx(x), vpToPx(y), vpToPx(x + width), vpToPx(y + height));
        auto roundRect = OH_Drawing_RoundRectCreate(rect,vpToPx(rx),vpToPx(ry));
        OH_Drawing_PathAddRoundRect(path_, roundRect, PATH_DIRECTION_CW);
        return path_;
    };
};

} // namespace rnoh