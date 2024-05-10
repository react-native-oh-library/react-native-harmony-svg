#include "RNSVGDefsComponentInstance.h"
#include "Props.h"
#include "SvgGroup.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGDefsComponentInstance::RNSVGDefsComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGroup>());
}

void RNSVGDefsComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);

     GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGDefsComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
