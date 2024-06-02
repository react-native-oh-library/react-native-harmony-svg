#include "RNSVGPathComponentInstance.h"
#include "SvgPath.h"

namespace rnoh {
namespace svg {

RNSVGPathComponentInstance::RNSVGPathComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgPath>());
}

void RNSVGPathComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[RNSVGPathComponentInstance] d: " << props->d;
    auto svgPath = std::dynamic_pointer_cast<SvgPath>(GetSvgNode());
    svgPath->UpdateCommonProps(props);
    svgPath->setD(props->d);
}

} // namespace svg
} // namespace rnoh
