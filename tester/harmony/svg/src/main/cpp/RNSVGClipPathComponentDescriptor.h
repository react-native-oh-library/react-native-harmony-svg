#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>

namespace facebook {
namespace react {

extern const char RNSVGClipPathComponentName[] = "RNSVGClipPath";

class RNSVGClipPathProps : public ViewProps {
  public:
    RNSVGClipPathProps() = default;

    RNSVGClipPathProps(const PropsParserContext &context, const RNSVGClipPathProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps) {}
};

using RNSVGClipPathShadowNode = ConcreteViewShadowNode<
    RNSVGClipPathComponentName,
    RNSVGClipPathProps,
    ViewEventEmitter>;

class RNSVGClipPathComponentDescriptor final
    : public ConcreteComponentDescriptor<RNSVGClipPathShadowNode> {
  public:
    RNSVGClipPathComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
