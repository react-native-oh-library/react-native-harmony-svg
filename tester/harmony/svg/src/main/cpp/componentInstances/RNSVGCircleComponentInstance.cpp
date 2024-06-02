#include "RNSVGCircleComponentInstance.h"
#include "Props.h"
#include "SvgCircle.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGCircleComponentInstance::RNSVGCircleComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGCircleComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[RNSVGCircleComponentInstance] cx: " << props->cx;
    DLOG(INFO) << "[RNSVGCircleComponentInstance] cy: " << props->cy;
    DLOG(INFO) << "[RNSVGCircleComponentInstance] r: " << props->r;
    DLOG(INFO) << "[RNSVGCircleComponentInstance] opacity: " << props->opacity;
    DLOG(INFO) << "[RNSVGCircleComponentInstance] fill.payload: " << (uint32_t)*props->fill.payload;
    DLOG(INFO) << "[RNSVGCircleComponentInstance] mask: " << props->mask;
    DLOG(INFO) << "[SVG] <RNSVGCircleComponentInstance> propList size = " << props->propList.size();
    for (auto prop : props->propList) {
        DLOG(INFO) << "[SVG] <RNSVGCircleComponentInstance> prop: " << prop;
    }

    // set attribute to svgCircle.
    auto svgCircle = std::dynamic_pointer_cast<SvgCircle>(GetSvgNode());
    svgCircle->UpdateCommonProps(props);
    svgCircle->SetX(props->cx);
    svgCircle->SetY(props->cy);
    svgCircle->SetR(props->r);
}
} // namespace svg
} // namespace rnoh
