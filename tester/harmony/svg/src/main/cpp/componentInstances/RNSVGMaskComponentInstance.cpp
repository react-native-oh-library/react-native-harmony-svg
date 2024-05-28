#include "RNSVGMaskComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgQuote.h"
#include "utils/StringUtils.h"

namespace rnoh {
namespace svg {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    LOG(INFO) << "[RNSVGMaskComponentInstance] RNSVGMaskComponentInstance: ";
    SetSvgNode(std::make_shared<SvgMask>());
}
void RNSVGMaskComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged x: " << props->x;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged y: " << props->y;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged height: " << props->height;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged width: " << props->width;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged maskUnits: " << props->maskUnits;
    LOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged maskContentUnits: " << props->maskContentUnits;
    auto svgMask = std::dynamic_pointer_cast<SvgMask>(GetSvgNode());
    svgMask->UpdateCommonProps(props);
    // set attribute to svgMask.
    svgMask->setMaskX(StringUtils::StringToDimension(props->x,true));
    svgMask->setMaskY(StringUtils::StringToDimension(props->y,true));
    svgMask->setMaskHeight(StringUtils::StringToDimension(props->height,true));
    svgMask->setMaskWidth(StringUtils::StringToDimension(props->width,true));
    svgMask->isDefaultMaskUnits(props->maskUnits == 0); // means objectBoundingBox
    svgMask->isDefaultMaskContentUnits(props->maskContentUnits == 1);// means userSpaceOnUse
}

} // namespace svg
} // namespace rnoh
