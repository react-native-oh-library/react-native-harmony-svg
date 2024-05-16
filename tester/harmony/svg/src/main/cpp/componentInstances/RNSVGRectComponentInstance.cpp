#include "RNSVGRectComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGRectComponentInstance::RNSVGRectComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgRect>());
}

void RNSVGRectComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->fill.payload: " << (uint32_t)*props->fill.payload;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->stroke.payload: " << (uint32_t)*props->stroke.payload;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->stroke.payload meaningful: " << facebook::react::isColorMeaningful(props->stroke.payload);
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->stroke.type: " << props->stroke.type;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->stroke.brushRef: " << props->stroke.brushRef;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->strokeWidth: " << props->strokeWidth;
    LOG(INFO) << "[RNSVGRectComponentInstance] Props->propList size: " << props->propList.size();
    for (auto &prop : props->propList) {
        LOG(INFO) << "[RNSVGRectComponentInstance] Props->propList: " << prop;
    }
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

    svgRect->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGRectComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace svg
} // namespace rnoh
