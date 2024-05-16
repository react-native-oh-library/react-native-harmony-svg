#include "RNSVGDefsComponentInstance.h"
#include "Props.h"
#include "SvgGroup.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGDefsComponentInstance::RNSVGDefsComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgDefs>());
}

void RNSVGDefsComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }

     GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGDefsComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
