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
    svgMask->setMaskUnits(props->maskUnits);
    svgMask->setMaskContentUnits(props->maskContentUnits);
    svgMask->setMaskX(props->x);
    svgMask->setMaskY(props->y);
    svgMask->setMaskHeight(props->height);
    svgMask->setMaskWidth(props->width);
}

} // namespace svg
} // namespace rnoh
