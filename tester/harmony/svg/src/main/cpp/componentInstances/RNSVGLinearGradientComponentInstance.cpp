#include "RNSVGLinearGradientComponentInstance.h"
#include "SvgGradient.h"

namespace rnoh {
namespace svg {

RNSVGLinearGradientComponentInstance::RNSVGLinearGradientComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGradient>(GradientType::LINEAR));
}

void RNSVGLinearGradientComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    auto svgGradient = std::dynamic_pointer_cast<SvgGradient>(GetSvgNode());
    svgGradient->UpdateHrefRenderProps(props);
    svgGradient->SetAttrGradientUnits(props->gradientUnits); // first set attr gradientUnits
    svgGradient->SetAttrX1(props->x1);
    svgGradient->SetAttrY1(props->y1);
    svgGradient->SetAttrX2(props->x2);
    svgGradient->SetAttrY2(props->y2);
    svgGradient->SetAttrGradient(props->gradient);
    svgGradient->SetAttrGradientTransforms(props->gradientTransform);
}

} // namespace svg
} // namespace rnoh
