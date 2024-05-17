#include "RNSVGTextComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgTSpan.h"

namespace rnoh {
namespace svg {

RNSVGTextComponentInstance::RNSVGTextComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgText);
}

void RNSVGTextComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
          

    m_svgText->UpdateFontProps(props);
    m_svgText->UpdateTextProps(props);
}

} // namespace svg
} // namespace rnoh
