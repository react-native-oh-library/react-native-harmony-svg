#include "RNSVGTSpanComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <SvgTSpan.h>

namespace rnoh {
namespace svg {

RNSVGTSpanComponentInstance::RNSVGTSpanComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgTSpan);
}

void RNSVGTSpanComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
            
    m_svgTSpan->content_ = props->content;

    m_svgTSpan->UpdateFontProps(props);
    m_svgTSpan->UpdateTextProps(props);
}


} // namespace svg
} // namespace rnoh
