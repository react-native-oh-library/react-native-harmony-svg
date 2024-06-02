#include "RNSVGEllipseComponentInstance.h"
#include "SvgEllipse.h"

namespace rnoh {
namespace svg {

RNSVGEllipseComponentInstance::RNSVGEllipseComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgEllipse>());
}

void RNSVGEllipseComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[SvgEllipse] cx: " << props->cx;
    DLOG(INFO) << "[SvgEllipse] cy: " << props->cy;
    DLOG(INFO) << "[SvgEllipse] rx: " << props->rx;
    DLOG(INFO) << "[SvgEllipse] ry: " << props->ry;
    auto svgEllipse = std::dynamic_pointer_cast<SvgEllipse>(GetSvgNode());
    svgEllipse->UpdateCommonProps(props);
    svgEllipse->SetCX(props->cx);
    svgEllipse->SetCY(props->cy);
    svgEllipse->SetRX(props->rx);
    svgEllipse->SetRY(props->ry);
}

} // namespace svg
} // namespace rnoh
