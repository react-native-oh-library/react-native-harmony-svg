#include "SvgLine.h"

namespace rnoh {
namespace svg {

drawing::Path SvgLine::AsPath() {
    double x1 = relativeOnWidth(lineAttribute_.x1);
    double y1 = relativeOnWidth(lineAttribute_.y1);
    double x2 = relativeOnWidth(lineAttribute_.x2);
    double y2 = relativeOnWidth(lineAttribute_.y2);

    path_.MoveTo(x1, y1);
    path_.LineTo(x2, y2);
    
    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x1, y1)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x2, y2)})};
    return path_;
};

} // namespace svg
} // namespace rnoh