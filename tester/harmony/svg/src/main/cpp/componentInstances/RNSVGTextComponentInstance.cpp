#include "RNSVGTextComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGTextComponentInstance::RNSVGTextComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
//     SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGTextComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
     GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
}



SvgArkUINode &RNSVGTextComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
