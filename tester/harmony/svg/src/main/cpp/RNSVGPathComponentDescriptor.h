#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGPathComponentName[] = "RNSVGPath";

class RNSVGPathProps : public ViewProps {
  public:
    RNSVGPathProps() = default;

    RNSVGPathProps(const PropsParserContext &context, const RNSVGPathProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGPathShadowNode = ConcreteViewShadowNode<
    RNSVGPathComponentName,
    RNSVGPathProps,
    ViewEventEmitter>;

class RNSVGPathComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGPathShadowNode> {
  public:
    RNSVGPathComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
