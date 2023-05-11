#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGGroupComponentName[] = "RNSVGGroup";

class RNSVGGroupProps : public ViewProps {
  public:
    RNSVGGroupProps() = default;

    RNSVGGroupProps(const PropsParserContext &context, const RNSVGGroupProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGGroupShadowNode = ConcreteViewShadowNode<
    RNSVGGroupComponentName,
    RNSVGGroupProps,
    ViewEventEmitter>;

class RNSVGGroupComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGGroupShadowNode> {
  public:
    RNSVGGroupComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
