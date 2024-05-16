#include "RNSVGImageComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgCircle.h"

namespace rnoh {
namespace svg {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(std::make_shared<SvgCircle>());
}

void RNSVGImageComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
      
      
}


} // namespace svg
} // namespace rnoh
