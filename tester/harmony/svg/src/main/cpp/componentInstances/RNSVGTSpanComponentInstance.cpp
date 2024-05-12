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

    m_svgTSpan->UpdateTextProps(props);
}

SvgArkUINode &RNSVGTSpanComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }
    void RNSVGTSpanComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index){
        auto child = std::dynamic_pointer_cast<SvgHost>(childComponentInstance);
        if (!child) {
            return;
        }
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(child));
        if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child->GetSvgNode())) {
            tSpan->SetParent(m_svgTSpan);
        }
    }

} // namespace rnoh
