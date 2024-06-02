#include "RNSVGGroupComponentInstance.h"
#include "SvgGroup.h"

namespace rnoh {
namespace svg {

RNSVGGroupComponentInstance::RNSVGGroupComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGroup>());
}

void RNSVGGroupComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    DLOG(INFO) << "[RNSVGGroupComponentInstance] props->fill.payload: " << (uint32_t)*props->fill.payload;

    auto group = std::dynamic_pointer_cast<SvgGroup>(GetSvgNode());
    group->UpdateCommonProps(props);
    group->UpdateFontProps(props);
}
} // namespace svg
} // namespace rnoh