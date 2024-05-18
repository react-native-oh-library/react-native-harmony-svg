#include "RNSVGGroupComponentInstance.h"
#include "Props.h"
#include <memory>
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGGroupComponentInstance::RNSVGGroupComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgGroup>());
}

void RNSVGGroupComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    LOG(INFO) << "[RNSVGGroupComponentInstance] props->fill.payload: " << (uint32_t)*props->fill.payload;

    auto group = std::dynamic_pointer_cast<SvgGroup>(GetSvgNode());
    group->UpdateFontProps(props);
}
} // namespace svg
}