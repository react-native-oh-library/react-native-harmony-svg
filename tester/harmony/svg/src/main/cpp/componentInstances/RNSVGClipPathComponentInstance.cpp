#include "RNSVGClipPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGClipPathComponentInstance::RNSVGClipPathComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
//     SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGClipPathComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);

     GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
}

SvgArkUINode &RNSVGClipPathComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
