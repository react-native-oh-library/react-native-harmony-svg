#include "RNSVGLineComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGLineComponentInstance::RNSVGLineComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgLine>());
}

void RNSVGLineComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGLineComponentInstance] Props->fill.payload: " << (uint32_t)*props->fill.payload;
    LOG(INFO) << "[RNSVGLineComponentInstance] Props->stroke.payload: " << (uint32_t)*props->stroke.payload;
    LOG(INFO) << "[RNSVGLineComponentInstance] props->strokeLinecap: " << props->strokeLinecap;
    LOG(INFO) << "[RNSVGLineComponentInstance] props->strokeLinejoin: " << props->strokeLinejoin;
//     LOG(INFO) << "[RNSVGLineComponentInstance] props->strokeDasharray: " << props->strokeDasharray[0];
    auto svgLine = std::dynamic_pointer_cast<SvgLine>(GetSvgNode());
    svgLine->x1 = std::stod(props->x1);
    svgLine->y1 = std::stod(props->y1);
    svgLine->x2 = std::stod(props->x2);
    svgLine->y2 = std::stod(props->y2);

    svgLine->setBrushColor((uint32_t)*props->fill.payload);
    
    svgLine->setStrokColor((uint32_t)*props->stroke.payload);
    svgLine->setStrokeLineWith(props->strokeWidth);
    svgLine->setStrokeDasharray(props->strokeDasharray);
    svgLine->setStrokeDashoffset(props->strokeDashoffset);
    svgLine->setStrokeLineCap(props->strokeLinecap);
    svgLine->setStrokeLineJoin(props->strokeLinejoin);
    svgLine->setStrokeMiterlimit(props->strokeMiterlimit);
    svgLine->setStrokeOpacity(props->strokeOpacity);

    //     svgLine->SetAttr("strokeWidth", props->strokeWidth);
    //     svgLine->SetAttr("strokeDashoffset", std::to_string(props->strokeDashoffset));
    //     svgLine->SetAttr("strokeLinecap", std::to_string(props->strokeLinecap));
    //     svgLine->SetAttr("strokeLinejoin", std::to_string(props->strokeLinejoin));
    
}

SvgArkUINode &RNSVGLineComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
