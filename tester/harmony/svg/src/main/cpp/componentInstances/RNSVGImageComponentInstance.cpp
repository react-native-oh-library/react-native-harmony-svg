#include "RNSVGImageComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgCircle.h"

namespace rnoh {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGImageComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }

     GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGImageComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
