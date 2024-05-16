#include "RNSVGLinearGradientComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgGradient.h"
#include "./utils/StringUtils.h"

namespace rnoh {

RNSVGLinearGradientComponentInstance::RNSVGLinearGradientComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGradient>(GradientType::LINEAR));
}

void RNSVGLinearGradientComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
    auto svgGradient = std::dynamic_pointer_cast<SvgGradient>(GetSvgNode());
    svgGradient->SetAttrX1(props->x1);
    svgGradient->SetAttrY1(props->y1);
    svgGradient->SetAttrX2(props->x2);
    svgGradient->SetAttrY2(props->y2);
    svgGradient->SetAttrGradient(props->gradient);
    svgGradient->SetAttrGradientUnits(props->gradientUnits);
    svgGradient->SetAttrGradientTransforms(props->gradientTransform);

    svgGradient->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGLinearGradientComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
