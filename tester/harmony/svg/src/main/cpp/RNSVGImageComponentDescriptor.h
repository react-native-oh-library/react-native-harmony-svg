#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGImageComponentName[] = "RNSVGImage";

class RNSVGImageProps : public ViewProps {
  public:
    RNSVGImageProps() = default;

    RNSVGImageProps(const PropsParserContext &context, const RNSVGImageProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGImageShadowNode = ConcreteViewShadowNode<
    RNSVGImageComponentName,
    RNSVGImageProps,
    ViewEventEmitter>;

class RNSVGImageComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGImageShadowNode> {
  public:
    RNSVGImageComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
