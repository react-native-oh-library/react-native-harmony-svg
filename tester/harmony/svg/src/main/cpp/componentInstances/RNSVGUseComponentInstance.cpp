#include "RNSVGUseComponentInstance.h"
#include "SvgUse.h"

namespace rnoh {
namespace svg {

RNSVGUseComponentInstance::RNSVGUseComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgUse>());
}

void RNSVGUseComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[RNSvgUseComponentInstance] Props: ";
    DLOG(INFO) << "[RNSvgUseComponentInstance] x: " << props->x;
    DLOG(INFO) << "[RNSvgUseComponentInstance] y: " << props->y;
    DLOG(INFO) << "[RNSvgUseComponentInstance] width: " << props->width;
    DLOG(INFO) << "[RNSvgUseComponentInstance] height: " << props->height;
    // DLOG(INFO) << "[RNSvgUseComponentInstance] opacity: " << props->opacity;
    DLOG(INFO) << "[RNSvgUseComponentInstance] href: " << props->href;

    auto svgUse = std::dynamic_pointer_cast<SvgUse>(GetSvgNode());
    svgUse->UpdateCommonProps(props);
    svgUse->x = std::stof(props->x);
    svgUse->y = std::stof(props->y);
    svgUse->width = std::stof(props->width);
    svgUse->height = std::stof(props->height);
    svgUse->href = props->href;
}

} // namespace svg
} // namespace rnoh
