#include "RNSVGLineComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "properties/Color.h"

namespace rnoh {
namespace svg {

RNSVGLineComponentInstance::RNSVGLineComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgLine>());
}

void RNSVGLineComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
         LOG(INFO) << "[RNSVGLineComponentInstance] Props->fill.payload: "
              << Color((uint32_t)*props->fill.payload).ToString();
    LOG(INFO) << "[RNSVGLineComponentInstance] Props->stroke.payload: "
              << Color((uint32_t)*props->stroke.payload).ToString();
    LOG(INFO) << "[RNSVGLineComponentInstance] props->strokeLinecap: " << props->strokeLinecap;
    LOG(INFO) << "[RNSVGLineComponentInstance] props->strokeLinejoin: " << props->strokeLinejoin;
    LOG(INFO) << "[SVG] <RNSVGLineComponentInstance> propList size = " << props->propList.size();
    for (auto prop : props->propList) {
        LOG(INFO) << "[SVG] <RNSVGLineComponentInstance> prop: " << prop;
    }
    //     LOG(INFO) << "[RNSVGLineComponentInstance] props->strokeDasharray: " << props->strokeDasharray[0];
    auto svgLine = std::dynamic_pointer_cast<SvgLine>(GetSvgNode());
    svgLine->x1 = std::stod(props->x1);
    svgLine->y1 = std::stod(props->y1);
    svgLine->x2 = std::stod(props->x2);
    svgLine->y2 = std::stod(props->y2);

}


} // namespace svg
} // namespace rnoh
