#include "RNSVGMaskComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgQuote.h"
#include "utils/StringUtils.h"

namespace rnoh {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    LOG(INFO) << "[RNSVGMaskComponentInstance] RNSVGMaskComponentInstance: ";
//     SetSvgNode(std::make_shared<SvgQuote>());
    SetSvgNode(std::make_shared<SvgMask>());
    m_svgArkUINode.SetSvgNode(GetSvgNode());
}

void RNSVGMaskComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->x;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->y;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->height;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->width;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->maskUnits;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged: " << props->maskContentUnits;
    auto svgMask = std::dynamic_pointer_cast<SvgMask>(GetSvgNode());
    // set attribute to svgMask.
    svgMask->setMaskX(StringUtils::FromString(props->x));
    svgMask->setMaskY(StringUtils::FromString(props->y));
    svgMask->setMaskHeight(StringUtils::FromString(props->height));
    svgMask->setMaskWidth(StringUtils::FromString(props->width));
    svgMask->isDefaultMaskUnits(props->maskUnits == 1);
    svgMask->isDefaultMaskContentUnits(props->maskContentUnits == 1);
	GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
  
}

SvgArkUINode &RNSVGMaskComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
