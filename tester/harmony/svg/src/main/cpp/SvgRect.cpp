#include "SvgRect.h"

namespace rnoh {
namespace svg {

OH_Drawing_Path *SvgRect::AsPath() {
        LOG(INFO) << "[SvgRect] AsPath";
        //TODO implement ConvertDimensionToPx
        auto rect = OH_Drawing_RectCreate(vpToPx(x), vpToPx(y), vpToPx(x + width), vpToPx(y + height));
        auto roundRect = OH_Drawing_RoundRectCreate(rect,vpToPx(rx),vpToPx(ry));
        OH_Drawing_PathAddRoundRect(path_, roundRect, PATH_DIRECTION_CW);

        elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x, y)}),
                     PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x + width, y)}),
                     PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x + width, y + height)}),
                     PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y + height)}),
                     PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y)})};
        return path_;
    };

} // namespace svg
} // namespace rnoh


