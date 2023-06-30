#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGCircleComponentName[] = "RNSVGCircle";

class RNSVGCircleProps : public ViewProps {
  public:
    RNSVGCircleProps() = default;

    RNSVGCircleProps(const PropsParserContext &context, const RNSVGCircleProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGCircleShadowNode = ConcreteViewShadowNode<
    RNSVGCircleComponentName,
    RNSVGCircleProps,
    ViewEventEmitter>;

class RNSVGCircleComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGCircleShadowNode> {
  public:
    RNSVGCircleComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
