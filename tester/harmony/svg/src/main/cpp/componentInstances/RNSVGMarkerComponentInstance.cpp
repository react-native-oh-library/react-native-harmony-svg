#include "RNSVGMarkerComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgMarker.h"

namespace rnoh {

RNSVGMarkerComponentInstance::RNSVGMarkerComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgMarker>());
}

void RNSVGMarkerComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
     CppComponentInstance::onPropsChanged(props);
}

SvgArkUINode &RNSVGMarkerComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
