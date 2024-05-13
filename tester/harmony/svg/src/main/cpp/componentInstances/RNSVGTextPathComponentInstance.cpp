#include "RNSVGTextPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgTSpan.h"

namespace rnoh {

RNSVGTextPathComponentInstance::RNSVGTextPathComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(m_svgTP);
}

void RNSVGTextPathComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    GetSvgNode()->UpdateCommonProps(props);

    m_svgTP->UpdateFontProps(props);
    m_svgTP->UpdateTextProps(props);
    m_svgTP->href_ = props->href;
    m_svgTP->startOffset_ = StringUtils::FromString(props->startOffset).ConvertToPx();
}

    void RNSVGTextPathComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) {
        auto child = std::dynamic_pointer_cast<SvgHost>(childComponentInstance);
        if (!child) {
            return;
        }
        OnChildInsertCommon(child);
        LOG(INFO) << "TEXT_PATH insert child";
    }
} // namespace rnoh
