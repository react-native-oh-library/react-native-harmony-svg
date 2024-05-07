#include "RNSVGMaskComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
//     SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGMaskComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    
}

SvgArkUINode &RNSVGMaskComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
