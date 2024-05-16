#include "RNSVGUseComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGUseComponentInstance::RNSVGUseComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
     SetSvgNode(std::make_shared<SvgUse>());
}

void RNSVGUseComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
     GetSvgNode()->UpdateCommonProps(props);

     LOG(INFO) << "[RNSvgUseComponentInstance] Props: " ;
     LOG(INFO) << "[RNSvgUseComponentInstance] x: " << props->x;
     LOG(INFO) << "[RNSvgUseComponentInstance] y: " << props->y;
     LOG(INFO) << "[RNSvgUseComponentInstance] width: " << props->width;
     LOG(INFO) << "[RNSvgUseComponentInstance] height: " << props->height;
     // LOG(INFO) << "[RNSvgUseComponentInstance] opacity: " << props->opacity;
     LOG(INFO) << "[RNSvgUseComponentInstance] href: " << props->href;

     // set attribute to svgCircle.
     auto svgUse = std::dynamic_pointer_cast<SvgUse>(GetSvgNode());
     svgUse->x = std::stof(props->x);
     svgUse->y = std::stof(props->y);
     svgUse->width = std::stof(props->width);
     svgUse->height = std::stof(props->height);
     svgUse->href = props->href;
     // svgUse->UpdateCommonProps(props, svgUse);

}

SvgArkUINode &RNSVGUseComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace svg
} // namespace rnoh
