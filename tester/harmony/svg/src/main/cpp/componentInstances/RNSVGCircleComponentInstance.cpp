#include "RNSVGCircleComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGCircleComponentInstance::RNSVGCircleComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGCircleComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGCircleComponentInstance] cx: " << props->cx;
    LOG(INFO) << "[RNSVGCircleComponentInstance] cy: " << props->cy;
    LOG(INFO) << "[RNSVGCircleComponentInstance] r: " << props->r;
    LOG(INFO) << "[RNSVGCircleComponentInstance] r: " << props->opacity;
    LOG(INFO) << "[RNSVGCircleComponentInstance] fill.payload: " << (uint32_t)*props->fill.payload ;
    LOG(INFO) << "[RNSVGCircleComponentInstance] mask: " << props->mask;
    LOG(INFO) << "[SVG] <RNSVGCircleComponentInstance> propList size = " << props->propList.size();
    for (auto prop : props->propList) {
        LOG(INFO) << "[SVG] <RNSVGCircleComponentInstance> prop: " << prop;
    }
    // set attribute to svgCircle.
    auto svgCircle = std::dynamic_pointer_cast<SvgCircle>(GetSvgNode());
    svgCircle->x = std::stof(props->cx);
    svgCircle->y = std::stof(props->cy);
    svgCircle->r = std::stof(props->r);
    //透明度穿0.0-1.0 ，需要乘以100转换
    svgCircle->opacity = props->opacity*100;
    //颜色需要转换
    svgCircle->colorFill = (uint32_t)*props->fill.payload;
   
    svgCircle->UpdateCommonProps(props, svgCircle);
}

SvgArkUINode &RNSVGCircleComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
