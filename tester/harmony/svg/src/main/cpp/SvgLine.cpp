//
// Created on 6/5/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SvgLine.h"

namespace rnoh {
namespace svg {

drawing::Path SvgLine::AsPath() {
    LOG(INFO) << "[SvgLine] AsPath";
    // Test getRootViewBox
    LOG(INFO) << "[SvgLine] getRootViewBox: " << context_->GetRootViewBox().Left() << ", "
              << context_->GetRootViewBox().Top() << ", " << context_->GetRootViewBox().Right() << ", "
              << context_->GetRootViewBox().Bottom();
    OH_Drawing_PathMoveTo(path_.get(), vpToPx(x1), vpToPx(y1));
    OH_Drawing_PathLineTo(path_.get(), vpToPx(x2), vpToPx(y2));
    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x1, y1)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x2, y2)})};
    return path_;
};

} // namespace svg
} // namespace rnoh