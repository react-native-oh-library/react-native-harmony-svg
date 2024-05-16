#pragma once

#include "RNSVGBaseComponentInstance.h"    
#include "ShadowNodes.h"
#include "SvgGroup.h"

namespace rnoh {
namespace svg {
class RNSVGGroupComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGGroupShadowNode> {

 

public:
    RNSVGGroupComponentInstance(Context context);
    
    void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh