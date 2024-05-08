#include "RNSVGSvgViewComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgSvg.h"

namespace rnoh {

RNSVGSvgViewComponentInstance::RNSVGSvgViewComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgSvg>());
    m_svgArkUINode.SetSvgNode(GetSvgNode());
    GetSvgNode()->SetContext(std::make_shared<SvgContext>());
}

void RNSVGSvgViewComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->width: " << m_layoutMetrics.frame.size.width;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->height: " << m_layoutMetrics.frame.size.height;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->bbHeight: " << props->bbHeight;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->bbWidth: " << props->bbWidth;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->bbHeight: " << props->bbHeight;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->minX: " << props->minX;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->minY: " << props->minY;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->vbWidth: " << props->vbWidth;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->vbHeight: " << props->vbHeight;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->align: " << props->align;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->meetOrSlice: " << props->meetOrSlice;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->tintColor: " << props->tintColor;
    LOG(INFO) << "[SVG] <SVGViewComponentInstance> props->color: " << props->color;
    auto svg = dynamic_pointer_cast<SvgSvg>(GetSvgNode());
    svg->attr_.x = Dimension(props->minX);
    svg->attr_.y = Dimension(props->minY);
    svg->attr_.vbWidth = Dimension(props->vbWidth);
    svg->attr_.vbHeight = Dimension(props->vbHeight);
    svg->attr_.width = Dimension(props->bbWidth);
    svg->attr_.height = Dimension(props->bbHeight);
}

SvgArkUINode &RNSVGSvgViewComponentInstance::getLocalRootArkUINode() {
    return m_svgArkUINode;
}

} // namespace rnoh
