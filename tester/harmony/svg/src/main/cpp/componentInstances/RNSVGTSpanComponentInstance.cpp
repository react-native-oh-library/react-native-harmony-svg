#include "RNSVGTSpanComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <SvgTSpan.h>

namespace rnoh {

RNSVGTSpanComponentInstance::RNSVGTSpanComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(m_svgTSpan);
}

void RNSVGTSpanComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
     GetSvgNode()->UpdateCommonProps(props);
    m_svgTSpan->content = props->content;
    auto fontSize = StringUtils::FromString(props->font.fontSize);
    m_svgTSpan->fontSize = fontSize.ConvertToPx();

    m_svgTSpan->x.clear();
    for (auto const &value : props->x) {
        auto x = StringUtils::FromString(value);
        m_svgTSpan->x.push_back(x.ConvertToPx());
    }
    m_svgTSpan->y.clear();
    for (auto const &value : props->y) {
        auto y = StringUtils::FromString(value);
        m_svgTSpan->y.push_back(y.ConvertToPx());
    }
}

SvgArkUINode &RNSVGTSpanComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
