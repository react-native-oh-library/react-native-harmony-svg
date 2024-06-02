#include "RNSVGRadialGradientComponentInstance.h"
#include "SvgGradient.h"

namespace rnoh {
namespace svg {

RNSVGRadialGradientComponentInstance::RNSVGRadialGradientComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGradient>(GradientType::RADIAL));
}

void RNSVGRadialGradientComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {

    auto svgGradient = std::dynamic_pointer_cast<SvgGradient>(GetSvgNode());
    svgGradient->UpdateHrefRenderProps(props);
    svgGradient->SetAttrGradientUnits(props->gradientUnits); // first set attr gradientUnits
    svgGradient->SetAttrFx(props->fx);
    svgGradient->SetAttrFy(props->fy);
    svgGradient->SetAttrCx(props->cx);
    svgGradient->SetAttrCy(props->cy);
    svgGradient->SetAttrRx(props->rx);
    svgGradient->SetAttrRy(props->ry);
    svgGradient->SetAttrGradient(props->gradient);
    svgGradient->SetAttrGradientTransforms(props->gradientTransform);
}

} // namespace svg
} // namespace rnoh
