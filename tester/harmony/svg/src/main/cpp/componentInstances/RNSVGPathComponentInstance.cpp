#include "RNSVGPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {

RNSVGPathComponentInstance::RNSVGPathComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgPath>());
}

void RNSVGPathComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[RNSVGPathComponentInstance] d: " << props->d;
    auto svgPath = std::dynamic_pointer_cast<SvgPath>(GetSvgNode());
    svgPath->d = props->d;

    svgPath->UpdateCommonProps(props);
}


SvgArkUINode &RNSVGPathComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
