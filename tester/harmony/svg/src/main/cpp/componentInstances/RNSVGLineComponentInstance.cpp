#include "RNSVGLineComponentInstance.h"
#include "SvgLine.h"

namespace rnoh {
namespace svg {

RNSVGLineComponentInstance::RNSVGLineComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgLine>());
}

void RNSVGLineComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[RNSVGLineComponentInstance] Props->fill.payload: "
               << Color((uint32_t)*props->fill.payload).ToString();
    DLOG(INFO) << "[RNSVGLineComponentInstance] Props->stroke.payload: "
               << Color((uint32_t)*props->stroke.payload).ToString();
    DLOG(INFO) << "[RNSVGLineComponentInstance] props->strokeLinecap: " << props->strokeLinecap;
    DLOG(INFO) << "[RNSVGLineComponentInstance] props->strokeLinejoin: " << props->strokeLinejoin;
    DLOG(INFO) << "[SVG] <RNSVGLineComponentInstance> propList size = " << props->propList.size();
    for (auto prop : props->propList) {
        DLOG(INFO) << "[SVG] <RNSVGLineComponentInstance> prop: " << prop;
    }
    auto svgLine = std::dynamic_pointer_cast<SvgLine>(GetSvgNode());
    svgLine->UpdateCommonProps(props);
    svgLine->SetX1(props->x1);
    svgLine->SetY1(props->y1);
    svgLine->SetX2(props->x2);
    svgLine->SetY2(props->y2);
}

} // namespace svg
} // namespace rnoh
