#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "RNSVGEllipseComponentInstance.h"
#include "Props.h"
#include "SvgEllipse.h"


namespace rnoh {
namespace svg {

RNSVGEllipseComponentInstance::RNSVGEllipseComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgEllipse>());
}

void RNSVGEllipseComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    LOG(INFO) << "[SvgEllipse] cx: " << props->cx;
    LOG(INFO) << "[SvgEllipse] cy: " << props->cy;
    LOG(INFO) << "[SvgEllipse] rx: " << props->rx;
    LOG(INFO) << "[SvgEllipse] ry: " << props->ry;
    auto svgEllipse = std::dynamic_pointer_cast<SvgEllipse>(GetSvgNode());
    svgEllipse->SetCX(props->cx);
    svgEllipse->SetCY(props->cy);
    svgEllipse->SetRX(props->rx);
    svgEllipse->SetRY(props->ry);
}

} // namespace svg
} // namespace rnoh
