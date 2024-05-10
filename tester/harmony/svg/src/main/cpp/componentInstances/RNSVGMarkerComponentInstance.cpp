#include "RNSVGMarkerComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <string>
#include "SvgMarker.h"
#include "properties/Dimension.h"
#include "utils/StringUtils.h"


namespace rnoh {

RNSVGMarkerComponentInstance::RNSVGMarkerComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgMarker>());
}

void RNSVGMarkerComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "liwang----->[RNSVGMarkerComponentInstance] onPropsChanged markerWidth=" << props->markerWidth << " markerHeight=" << props->markerHeight;
    GetSvgNode()->UpdateCommonProps(props);
    auto svgMarker = std::dynamic_pointer_cast<SvgMarker>(GetSvgNode());
    svgMarker->setRefX(StringUtils::StringToDimensionWithUnit(props->refX));
    svgMarker->setRefY(StringUtils::StringToDimensionWithUnit(props->refY));
    svgMarker->setMarkerWidth(StringUtils::StringToDimensionWithUnit(props->markerWidth));
    svgMarker->setMarkerHeight(StringUtils::StringToDimensionWithUnit(props->markerHeight));
    svgMarker->setMarkerUnits(props->markerUnits);
    svgMarker->setOrient(props->orient);
    svgMarker->setMinX(props->minX);
    svgMarker->setMinY(props->minY);
    svgMarker->setVbWidth(props->vbWidth);
    svgMarker->setVbHeight(props->vbHeight);
    svgMarker->setAlign(props->align);
    svgMarker->setMeetOrSlice(props->meetOrSlice);
}

SvgArkUINode &RNSVGMarkerComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
