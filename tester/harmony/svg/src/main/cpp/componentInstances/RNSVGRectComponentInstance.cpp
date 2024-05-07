#include "RNSVGRectComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGRectComponentInstance::RNSVGRectComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgRect>());
}

void RNSVGRectComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->fill.payload: " << (uint32_t)*props->fill.payload;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->stroke.payload: " << (uint32_t)*props->stroke.payload;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->strokeWidth: " << props->strokeWidth;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->rx: " << props->rx;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->ry: " << props->ry;
    auto svgRect = std::dynamic_pointer_cast<SvgRect>(GetSvgNode());
    svgRect->x = std::stod(props->x);
    svgRect->y = std::stod(props->y);
    svgRect->width = std::stod(props->width);
    svgRect->height = std::stod(props->height);
    if (props->rx.size() != 0) {
        // TODO fix: use std::stod cpp crash
        svgRect->rx = std::stof(props->rx);
    }
    if (props->ry.size() != 0) {
        // TODO fix: use std::stod cpp crash
        svgRect->ry = std::stof(props->ry);
    }
    svgRect->setBrushColor((uint32_t)*props->fill.payload);
    svgRect->setStrokColor((uint32_t)*props->stroke.payload);
//     svgRect->setStrokeLineWith(std::stod(props->strokeWidth));
    svgRect->SetAttr("strokeWidth", props->strokeWidth);
//     svgRect->SetAttr("strokeDashoffset",std::to_string(props->strokeDashoffset));
//     svgRect->SetAttr("strokeLinecap", std::to_string(props->strokeLinecap));
//     svgRect->SetAttr("strokeLinejoin", std::to_string(props->strokeLinejoin));
}

SvgArkUINode &RNSVGRectComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
