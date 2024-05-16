#include "RNSVGClipPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgClipPath.h"

namespace rnoh {
namespace svg {

RNSVGClipPathComponentInstance::RNSVGClipPathComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgClipPath>());
}

void RNSVGClipPathComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
    LOG(INFO) << "[RNSVGClipPathComponentInstance] onPropsChanged props name = " << props->name;
}

} // namespace svg
} // namespace rnoh
