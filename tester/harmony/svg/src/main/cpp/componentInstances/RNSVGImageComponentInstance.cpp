#include "RNSVGImageComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <SvgImage.h>

namespace rnoh {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgImage>());
}

void RNSVGImageComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    GetSvgNode()->UpdateCommonProps(props);
    auto svgImage = std::dynamic_pointer_cast<SvgImage>(GetSvgNode());
    svgImage->x = std::stof(props->x);
    svgImage->y = std::stof(props->y);
    svgImage->width = std::stof(props->width);
    svgImage->height = std::stof(props->height);
    svgImage->opacity = props->opacity;
    svgImage->src = props->src;
}

SvgArkUINode &RNSVGImageComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
