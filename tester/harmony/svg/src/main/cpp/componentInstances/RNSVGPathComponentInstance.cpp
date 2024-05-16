#include "RNSVGPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>

namespace rnoh {
namespace svg {

RNSVGPathComponentInstance::RNSVGPathComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgPath>());
}

void RNSVGPathComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
          LOG(INFO) << "[RNSVGPathComponentInstance] d: " << props->d;
    auto svgPath = std::dynamic_pointer_cast<SvgPath>(GetSvgNode());
    svgPath->setD(props->d);

}



} // namespace svg
} // namespace rnoh
