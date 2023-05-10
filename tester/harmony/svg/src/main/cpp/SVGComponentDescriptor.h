#pragma once

#include <react/renderer/core/ConcreteComponentDescriptor.h>
#include "SVGShadowNode.h"

namespace facebook {
namespace react {

class SVGComponentDescriptor final
    : public ConcreteComponentDescriptor<SVGShadowNode> {
  public:
    SVGComponentDescriptor(ComponentDescriptorParameters const &parameters)
        : ConcreteComponentDescriptor(parameters) {}
};

} // namespace react
} // namespace facebook
