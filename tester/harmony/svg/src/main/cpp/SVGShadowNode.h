#pragma once

#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>
#include "SVGProps.h"

namespace facebook {
namespace react {

extern const char SVGComponentName[] = "SVG";

using SVGShadowNode = ConcreteViewShadowNode<
    SVGComponentName,
    SVGProps,
    ViewEventEmitter>;

} // namespace react
} // namespace facebook
