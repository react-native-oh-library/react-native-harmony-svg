#include "RNSVGMaskComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgQuote.h"

namespace rnoh {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    LOG(INFO) << "[RNSVGMaskComponentInstance] RNSVGMaskComponentInstance: ";
	//  SetSvgNode(std::make_shared<SvgQuote>());
    SetSvgNode(std::make_shared<SvgMask>());
    m_svgArkUINode.SetSvgNode(GetSvgNode());
}

void RNSVGMaskComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->height;
    auto svgMask = std::dynamic_pointer_cast<SvgMask>(GetSvgNode());
    // set attribute to svgMask.
	// GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
  
}

SvgArkUINode &RNSVGMaskComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
