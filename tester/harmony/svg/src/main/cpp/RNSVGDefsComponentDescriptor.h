#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGDefsComponentName[] = "RNSVGDefs";

class RNSVGDefsProps : public ViewProps {
  public:
    RNSVGDefsProps() = default;

    RNSVGDefsProps(const PropsParserContext &context, const RNSVGDefsProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGDefsShadowNode = ConcreteViewShadowNode<
    RNSVGDefsComponentName,
    RNSVGDefsProps,
    ViewEventEmitter>;

class RNSVGDefsComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGDefsShadowNode> {
  public:
    RNSVGDefsComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
