#include "RNSVGUseComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGUseComponentInstance::RNSVGUseComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
//     SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGUseComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
     GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
}

SvgArkUINode &RNSVGUseComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
