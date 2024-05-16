#include "RNSVGLineComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "properties/Color.h"

namespace rnoh {

RNSVGLineComponentInstance::RNSVGLineComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgLine>());
}

void RNSVGLineComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
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

    svgLine->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGLineComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
