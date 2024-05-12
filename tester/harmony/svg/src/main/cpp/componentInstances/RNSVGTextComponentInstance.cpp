#include "RNSVGTextComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgTSpan.h"

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

    m_svgText->UpdateTextProps(props);
}

SvgArkUINode &RNSVGTextComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

    void RNSVGTextComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) {
        auto child = std::dynamic_pointer_cast<SvgHost>(childComponentInstance);
        if (!child) {
            return;
        }
        OnChildInsertCommon(child);
        if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child->GetSvgNode())) {
            tSpan->SetParent(m_svgText);
        }
    }
} // namespace rnoh
