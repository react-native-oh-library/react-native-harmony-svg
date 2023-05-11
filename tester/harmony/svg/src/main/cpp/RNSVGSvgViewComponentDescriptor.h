#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGSvgViewComponentName[] = "RNSVGSvgView";

class RNSVGSvgViewProps : public ViewProps {
  public:
    RNSVGSvgViewProps() = default;

    RNSVGSvgViewProps(const PropsParserContext &context, const RNSVGSvgViewProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGSvgViewShadowNode = ConcreteViewShadowNode<
    RNSVGSvgViewComponentName,
    RNSVGSvgViewProps,
    ViewEventEmitter>;

class RNSVGSvgViewComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGSvgViewShadowNode> {
  public:
    RNSVGSvgViewComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
