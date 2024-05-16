#include "RNSVGEllipseComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGEllipseComponentInstance::RNSVGEllipseComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgEllipse>());
}

void RNSVGEllipseComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
    LOG(INFO) << "[SvgEllipse] cx: " << props->cx;
    LOG(INFO) << "[SvgEllipse] cy: " << props->cy;
    LOG(INFO) << "[SvgEllipse] rx: " << props->rx;
    LOG(INFO) << "[SvgEllipse] ry: " << props->ry;
    auto svgEllipse = std::dynamic_pointer_cast<SvgEllipse>(GetSvgNode());
    svgEllipse->cx = std::stof(props->cx);
    svgEllipse->cy = std::stof(props->cy);
    svgEllipse->rx = std::stof(props->rx);
    svgEllipse->ry = std::stof(props->ry);
    svgEllipse->colorFill = (uint32_t)*props->fill.payload;

    GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGEllipseComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace svg
} // namespace rnoh
