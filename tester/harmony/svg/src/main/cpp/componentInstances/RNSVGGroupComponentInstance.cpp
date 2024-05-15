#include "RNSVGGroupComponentInstance.h"
#include "Props.h"
#include <memory>
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGGroupComponentInstance::RNSVGGroupComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGroup>());
}

void RNSVGGroupComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGGroupComponentInstance] props->fill.payload: " << (uint32_t)*props->fill.payload;

    auto group = std::dynamic_pointer_cast<SvgGroup>(GetSvgNode());
    group->UpdateCommonProps(props);
    group->UpdateFontProps(props);
}

SvgArkUINode &RNSVGGroupComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace svg
} // namespace rnoh
