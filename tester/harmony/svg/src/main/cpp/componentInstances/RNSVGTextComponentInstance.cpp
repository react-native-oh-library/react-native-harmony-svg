#include "RNSVGTextComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGTextComponentInstance::RNSVGTextComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(m_svgText);
}

void RNSVGTextComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    GetSvgNode()->UpdateCommonProps(props);

    auto propsFontSize = props->font.fontSize;
    auto fontSize = StringUtils::FromString(propsFontSize.empty() ? "16" : propsFontSize);
    m_svgText->fontSize = fontSize.ConvertToPx();

    m_svgText->x.clear();
    for (auto const &value : props->x) {
        auto x = StringUtils::FromString(value);
        m_svgText->x.push_back(x.ConvertToPx());
    }
    m_svgText->y.clear();
    for (auto const &value : props->y) {
        auto y = StringUtils::FromString(value);
        m_svgText->y.push_back(y.ConvertToPx());
    }
}


SvgArkUINode &RNSVGTextComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
