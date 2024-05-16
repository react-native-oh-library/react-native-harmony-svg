#include "RNSVGClipPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgClipPath.h"

namespace rnoh {
namespace svg {

RNSVGClipPathComponentInstance::RNSVGClipPathComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgClipPath>());
}

void RNSVGClipPathComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    LOG(INFO) << "[RNSVGClipPathComponentInstance] onPropsChanged props name = " << props->name;
    CppComponentInstance::onPropsChanged(props);
    // TODO: move ArkUINode to base class and use template function
    if (!props->responsible) {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
    } else {
        m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
    }
    GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGClipPathComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace svg
} // namespace rnoh
