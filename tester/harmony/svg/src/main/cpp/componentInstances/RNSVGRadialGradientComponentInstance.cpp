#include "RNSVGRadialGradientComponentInstance.h"
#include "Props.h"
#include <native_drawing/drawing_shader_effect.h>
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgGradient.h"
#include "./utils/StringUtils.h"

namespace rnoh {

RNSVGRadialGradientComponentInstance::RNSVGRadialGradientComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGradient>(GradientType::RADIAL));
}

void RNSVGRadialGradientComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);

    auto svgGradient = std::dynamic_pointer_cast<SvgGradient>(GetSvgNode());
    svgGradient->SetAttrFx(props->fx);
    svgGradient->SetAttrFy(props->fy);
    svgGradient->SetAttrCx(props->cx);
    svgGradient->SetAttrCy(props->cy);
    svgGradient->SetAttrRx(props->rx);
    svgGradient->SetAttrRy(props->ry);
    svgGradient->SetAttrGradient(props->gradient);
    svgGradient->SetAttrGradientUnits(props->gradientUnits);
    svgGradient->SetAttrGradientTransforms(props->gradientTransform);

    svgGradient->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGRadialGradientComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
