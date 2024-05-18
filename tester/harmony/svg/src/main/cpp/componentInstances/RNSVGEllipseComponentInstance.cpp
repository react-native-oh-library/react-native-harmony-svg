#include "RNSVGEllipseComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

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
    svgEllipse->cx = std::stof(props->cx);
    svgEllipse->cy = std::stof(props->cy);
    svgEllipse->rx = std::stof(props->rx);
    svgEllipse->ry = std::stof(props->ry);
    svgEllipse->colorFill = (uint32_t)*props->fill.payload;
}


} // namespace svg
} // namespace rnoh
