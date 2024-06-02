#include "RNSVGMaskComponentInstance.h"
#include "SvgMask.h"

namespace rnoh {
namespace svg {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    DLOG(INFO) << "[RNSVGMaskComponentInstance] RNSVGMaskComponentInstance: ";
    SetSvgNode(std::make_shared<SvgMask>());
}

void RNSVGMaskComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged x: " << props->x;
    DLOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged y: " << props->y;
    DLOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged height: " << props->height;
    DLOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged width: " << props->width;
    DLOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged maskUnits: " << props->maskUnits;
    DLOG(INFO) << "[RNSVGMaskComponentInstance] onPropsChanged maskContentUnits: " << props->maskContentUnits;
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
