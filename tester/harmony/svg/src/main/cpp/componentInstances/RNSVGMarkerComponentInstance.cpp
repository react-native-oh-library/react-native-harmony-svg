#include "RNSVGMarkerComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <string>
#include "SvgMarker.h"
#include "properties/Dimension.h"
#include "utils/StringUtils.h"


namespace rnoh {
namespace svg {

RNSVGMarkerComponentInstance::RNSVGMarkerComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgMarker>());
}

void RNSVGMarkerComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {


    LOG(INFO) << "[RNSVGMarkerComponentInstance] onPropsChanged markerWidth=" << props->markerWidth
              << " markerHeight=" << props->markerHeight;
    LOG(INFO) << "[RNSVGMarkerComponentInstance] onPropsChanged refX=" << props->refX << " refY=" << props->refY;
    LOG(INFO) << "[RNSVGMarkerComponentInstance] onPropsChanged markerUnits=" << props->markerUnits
              << " orient=" << props->orient;
    LOG(INFO) << "[RNSVGMarkerComponentInstance] onPropsChanged minX=" << props->minX << " minY=" << props->minY;
    LOG(INFO) << "[RNSVGMarkerComponentInstance] onPropsChanged vbWidth=" << props->vbWidth
              << " vbHeight=" << props->vbHeight;
    LOG(INFO) << "[RNSVGMarkerComponentInstance] onPropsChanged align=" << props->align
              << " meetOrSlice=" << props->meetOrSlice;
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


} // namespace svg
} // namespace rnoh
