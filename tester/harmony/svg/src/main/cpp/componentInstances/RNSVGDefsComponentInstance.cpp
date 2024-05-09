#include "RNSVGDefsComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGDefsComponentInstance::RNSVGDefsComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgDefs>());
}

void RNSVGDefsComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);

     GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
}

SvgArkUINode &RNSVGDefsComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
