#include "RNSVGPatternComponentInstance.h"
#include "SvgPattern.h"

namespace rnoh {
namespace svg {

RNSVGPatternComponentInstance::RNSVGPatternComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    DLOG(INFO) << "[RNSVGPatternComponentInstance] init";
    SetSvgNode(std::make_shared<SvgPattern>());
}

void RNSVGPatternComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {

    DLOG(INFO) << "[RNSVGPatternComponentInstance] x: " << props->x;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] y: " << props->y;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] width: " << props->width;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] height: " << props->height;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] patternUnits: " << props->patternUnits;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] patternContentUnits: " << props->patternContentUnits;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] minX: " << props->minX;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] minY: " << props->minY;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] vbWidth: " << props->vbWidth;
    DLOG(INFO) << "[RNSVGPatternComponentInstance] vbHeight: " << props->vbHeight;
    // set attribute to svgPattern
    auto svgPattern = std::dynamic_pointer_cast<SvgPattern>(GetSvgNode());
    svgPattern->UpdateCommonProps(props);
    svgPattern->setPatternX(StringUtils::FromString(props->x));
    svgPattern->setPatternY(StringUtils::FromString(props->y));
    svgPattern->setWidth(StringUtils::FromString(props->width));
    svgPattern->setHeight(StringUtils::FromString(props->height));
    svgPattern->setPatternUnits(props->patternUnits);
    svgPattern->setPatternContentUnits(props->patternContentUnits);
    svgPattern->setViewBox(Rect(props->minX, props->minY, props->vbWidth, props->vbHeight));
    svgPattern->setmMinX(props->minX);
    svgPattern->setmMinY(props->minY);
    svgPattern->setmVbWidth(props->vbWidth);
    svgPattern->setmVbHeight(props->vbHeight);
    svgPattern->setmAlign(props->align);
    svgPattern->setmMeetOrSlice(props->meetOrSlice);
    svgPattern->setPatternTransforms(props->patternTransform);
}


} // namespace svg
} // namespace rnoh
