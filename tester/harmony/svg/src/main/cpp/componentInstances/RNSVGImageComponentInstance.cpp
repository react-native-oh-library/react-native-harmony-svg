#include "RNSVGImageComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgCircle.h"

namespace rnoh {
namespace svg {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGImageComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);

     GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGImageComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace svg
} // namespace rnoh
