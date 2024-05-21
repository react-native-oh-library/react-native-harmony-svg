#pragma once
#include "RNSVGBaseComponentInstance.h"  
#include "ShadowNodes.h"

namespace rnoh {
namespace svg {

class RNSVGLineComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGLineShadowNode> {
    
public:
    RNSVGLineComponentInstance(Context context);

     void UpdateElementProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh