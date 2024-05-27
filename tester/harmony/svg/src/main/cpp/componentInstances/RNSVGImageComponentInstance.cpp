#include "RNSVGImageComponentInstance.h"
#include "Props.h"
#include "utils/SvgAttributesParser.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <SvgImage.h>

namespace rnoh {
namespace svg {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgImage>());
}

void RNSVGImageComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {     
    auto svgImage = std::dynamic_pointer_cast<SvgImage>(GetSvgNode());
    svgImage->x = (float)relativeOnWidth(SvgAttributesParser::ParseDimension(props->x));
    svgImage->y = (float)relativeOnWidth(SvgAttributesParser::ParseDimension(props->y));
    svgImage->width = (float)relativeOnWidth(SvgAttributesParser::ParseDimension(props->width));
    svgImage->height = (float)relativeOnWidth(SvgAttributesParser::ParseDimension(props->height));
    svgImage->opacity = props->opacity;
    svgImage->src = props->src;
    svgImage->align = props->align;
    svgImage->meetOrSlice = props->meetOrSlice;
}

} // namespace svg
} // namespace rnoh
