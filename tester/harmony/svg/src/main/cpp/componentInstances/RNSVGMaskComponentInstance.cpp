#include "RNSVGMaskComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgQuote.h"

namespace rnoh {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgQuote>());
}

void RNSVGMaskComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[SVG] <SVGMaskComponentInstance> props->name: " << props->name;
     GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
}

SvgArkUINode &RNSVGMaskComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
