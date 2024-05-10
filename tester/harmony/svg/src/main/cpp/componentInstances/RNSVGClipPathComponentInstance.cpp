#include "RNSVGClipPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgClipPath.h"

namespace rnoh {

RNSVGClipPathComponentInstance::RNSVGClipPathComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgClipPath>());
}

void RNSVGClipPathComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    LOG(INFO) << "[RNSVGClipPathComponentInstance] onPropsChanged props name = " << props->name;
    CppComponentInstance::onPropsChanged(props);
    GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGClipPathComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
