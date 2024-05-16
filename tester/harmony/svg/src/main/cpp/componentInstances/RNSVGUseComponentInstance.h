
#pragma once
#include "RNSVGBaseCI.h"  
#include <math.h>  
#include "ShadowNodes.h"
#include "SvgUse.h"

namespace rnoh {
namespace svg {

class RNSVGUseComponentInstance : public RNSVGBaseCI<facebook::react::RNSVGUseShadowNode> {
public:
    RNSVGUseComponentInstance(Context context);
    void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh