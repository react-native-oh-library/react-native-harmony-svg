#include "RNSVGUseComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGUseComponentInstance::RNSVGUseComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgUse>());
}

void RNSVGUseComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    LOG(INFO) << "[RNSvgUseComponentInstance] Props: ";
    LOG(INFO) << "[RNSvgUseComponentInstance] x: " << props->x;
    LOG(INFO) << "[RNSvgUseComponentInstance] y: " << props->y;
    LOG(INFO) << "[RNSvgUseComponentInstance] width: " << props->width;
    LOG(INFO) << "[RNSvgUseComponentInstance] height: " << props->height;
    // LOG(INFO) << "[RNSvgUseComponentInstance] opacity: " << props->opacity;
    LOG(INFO) << "[RNSvgUseComponentInstance] href: " << props->href;

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
