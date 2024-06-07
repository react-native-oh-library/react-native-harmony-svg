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
    svgImage->SetX(props->x);
    svgImage->SetY(props->y);
    svgImage->SetWidth(props->width);
    svgImage->SetHeight(props->height);
    svgImage->SetAlign(props->align);
    svgImage->SetMeetOrSlice(props->meetOrSlice);
    svgImage->SetImageSource(props->src);
}

} // namespace svg
} // namespace rnoh
