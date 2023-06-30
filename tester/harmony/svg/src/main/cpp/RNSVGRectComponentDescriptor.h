#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGRectComponentName[] = "RNSVGRect";

class RNSVGRectProps : public ViewProps {
  public:
    RNSVGRectProps() = default;

    RNSVGRectProps(const PropsParserContext &context, const RNSVGRectProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGRectShadowNode = ConcreteViewShadowNode<
    RNSVGRectComponentName,
    RNSVGRectProps,
    ViewEventEmitter>;

class RNSVGRectComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGRectShadowNode> {
  public:
    RNSVGRectComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
