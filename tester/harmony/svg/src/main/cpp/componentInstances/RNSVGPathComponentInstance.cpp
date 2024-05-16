#include "RNSVGPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGPathComponentInstance::RNSVGPathComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgPath>());
}

void RNSVGPathComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
    LOG(INFO) << "[RNSVGPathComponentInstance] d: " << props->d;
    auto svgPath = std::dynamic_pointer_cast<SvgPath>(GetSvgNode());
    svgPath->d = props->d;

    svgPath->UpdateCommonProps(props);
}


SvgArkUINode &RNSVGPathComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
