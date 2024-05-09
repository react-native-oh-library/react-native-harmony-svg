#include "RNSVGPatternComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "utils/StringUtils.h"

namespace rnoh {

RNSVGPatternComponentInstance::RNSVGPatternComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    LOG(INFO) << "[RNSVGPatternComponentInstance] init" ;
    SetSvgNode(std::make_shared<SvgPattern>());
}

void RNSVGPatternComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    GetSvgNode()->UpdateCommonProps(props, GetSvgNode());
    LOG(INFO) << "[RNSVGPatternComponentInstance] x: " << props->x;
    LOG(INFO) << "[RNSVGPatternComponentInstance] y: " << props->y;
    LOG(INFO) << "[RNSVGPatternComponentInstance] width: " << props->width;
    LOG(INFO) << "[RNSVGPatternComponentInstance] height: " << props->height;
    LOG(INFO) << "[RNSVGPatternComponentInstance] patternUnits: " << props->patternUnits;
    LOG(INFO) << "[RNSVGPatternComponentInstance] patternContentUnits: " << props->patternContentUnits;
    LOG(INFO) << "[RNSVGPatternComponentInstance] minX: " << props->minX;
    LOG(INFO) << "[RNSVGPatternComponentInstance] minY: " << props->minY;
    LOG(INFO) << "[RNSVGPatternComponentInstance] vbWidth: " << props->vbWidth;
    LOG(INFO) << "[RNSVGPatternComponentInstance] vbHeight: " << props->vbHeight;
    // set attribute to svgPattern
    auto svgPattern = std::dynamic_pointer_cast<SvgPattern>(GetSvgNode());
    svgPattern->patternAttr_.x = SvgAttributesParser::ParseDimension(props->x);
    svgPattern->patternAttr_.y = SvgAttributesParser::ParseDimension(props->y);
    svgPattern->patternAttr_.width = SvgAttributesParser::ParseDimension(props->width);
    svgPattern->patternAttr_.height = SvgAttributesParser::ParseDimension(props->height);
    svgPattern->patternAttr_.patternUnits = props->patternUnits == 1 ? "userSpaceOnUse" : "objectBoundingBox";
    svgPattern->patternAttr_.patternContentUnits = props->patternContentUnits == 1 ? "userSpaceOnUse" : "objectBoundingBox";
    svgPattern->patternAttr_.viewBox = Rect(props->minX, props->minY, props->vbWidth, props->vbHeight);
}

SvgArkUINode &RNSVGPatternComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
