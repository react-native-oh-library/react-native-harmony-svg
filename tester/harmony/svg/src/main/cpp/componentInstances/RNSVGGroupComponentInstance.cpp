#include "RNSVGGroupComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGGroupComponentInstance::RNSVGGroupComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGroup>());
}

void RNSVGGroupComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGGroupComponentInstance] props->fill.payload: " << (uint32_t)*props->fill.payload;

    GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGGroupComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
