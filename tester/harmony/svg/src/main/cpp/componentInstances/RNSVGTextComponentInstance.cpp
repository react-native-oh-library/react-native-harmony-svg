#include "RNSVGTextComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGTextComponentInstance::RNSVGTextComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgText);
}

void RNSVGTextComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    m_svgText->UpdateCommonProps(props);
    m_svgText->UpdateFontProps(props);
    m_svgText->UpdateTextProps(props);
}

} // namespace svg
} // namespace rnoh
