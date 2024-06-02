#include "RNSVGImageComponentInstance.h"
#include "SvgImage.h"

namespace rnoh {
namespace svg {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgImage>());
}

void RNSVGImageComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    auto svgImage = std::dynamic_pointer_cast<SvgImage>(GetSvgNode());
    svgImage->UpdateCommonProps(props);
    svgImage->x = std::stof(props->x);
    svgImage->y = std::stof(props->y);
    svgImage->width = std::stof(props->width);
    svgImage->height = std::stof(props->height);
    svgImage->opacity = props->opacity;
    svgImage->src = props->src;
    svgImage->align = props->align;
    svgImage->meetOrSlice = props->meetOrSlice;
}

} // namespace svg
} // namespace rnoh
