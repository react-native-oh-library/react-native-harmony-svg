#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGLinearGradientComponentName[] = "RNSVGLinearGradient";

class RNSVGLinearGradientProps : public ViewProps {
  public:
    RNSVGLinearGradientProps() = default;

    RNSVGLinearGradientProps(const PropsParserContext &context, const RNSVGLinearGradientProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGLinearGradientShadowNode = ConcreteViewShadowNode<
    RNSVGLinearGradientComponentName,
    RNSVGLinearGradientProps,
    ViewEventEmitter>;

class RNSVGLinearGradientComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGLinearGradientShadowNode> {
  public:
    RNSVGLinearGradientComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
