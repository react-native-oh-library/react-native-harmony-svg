#include "SvgRect.h"
#include "drawing/Rect.h"

namespace rnoh {
namespace svg {

drawing::Path SvgRect::AsPath() {
    drawing::Path path;
    double x = relativeOnWidth(rectAttribute_.x);
    double y = relativeOnHeight(rectAttribute_.y);
    double width = relativeOnWidth(rectAttribute_.width);
    double height = relativeOnHeight(rectAttribute_.height);

    if (rectAttribute_.rx != Dimension(-1.0, DimensionUnit::PX) ||
        rectAttribute_.ry != Dimension(-1.0, DimensionUnit::PX)) {
        double rx;
        double ry;
        if (rectAttribute_.rx == Dimension(-1.0, DimensionUnit::PX)) {
            ry = relativeOnHeight(rectAttribute_.ry);
            rx = ry;
        } else if (rectAttribute_.ry == Dimension(-1.0, DimensionUnit::PX)) {
            rx = relativeOnWidth(rectAttribute_.rx);
            ry = rx;
        } else {
            rx = relativeOnWidth(rectAttribute_.rx);
            ry = relativeOnHeight(rectAttribute_.ry);
        }
        
        if (rx > width / 2.0) {
            rx = width / 2.0;
        }

        if (ry > height / 2.0) {
            ry = height / 2.0;
        }
        drawing::Rect rect(x, y, x + width, y + height);
        drawing::RoundRect roundRect(std::move(rect), rx, ry);
        path.AddRoundRect(roundRect, PATH_DIRECTION_CW);
    } else {
        path.AddRect(x, y, x + width, y + height, PATH_DIRECTION_CW);
    }

    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x, y)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x + width, y)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x + width, y + height)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y + height)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y)})};
    return path;
};

} // namespace svg
} // namespace rnoh
