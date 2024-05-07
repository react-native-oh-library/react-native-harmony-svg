#include "RNSVGTSpanComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGTSpanComponentInstance::RNSVGTSpanComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
//     SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGTSpanComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
}

SvgArkUINode &RNSVGTSpanComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
