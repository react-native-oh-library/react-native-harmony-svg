#include "RNSVGClipPathComponentInstance.h"
#include "SvgClipPath.h"
#include <react/renderer/core/ConcreteState.h>

namespace rnoh {
namespace svg {

RNSVGClipPathComponentInstance::RNSVGClipPathComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgClipPath>());
}

void RNSVGClipPathComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    auto svgClipPath = std::dynamic_pointer_cast<SvgClipPath>(GetSvgNode());
    svgClipPath->UpdateCommonProps(props);
}

} // namespace svg
} // namespace rnoh
