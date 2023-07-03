#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGStopComponentName[] = "RNSVGStop";

class RNSVGStopProps : public ViewProps {
  public:
    RNSVGStopProps() = default;

    RNSVGStopProps(const PropsParserContext &context, const RNSVGStopProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGStopShadowNode = ConcreteViewShadowNode<
    RNSVGStopComponentName,
    RNSVGStopProps,
    ViewEventEmitter>;

class RNSVGStopComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGStopShadowNode> {
  public:
    RNSVGStopComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
