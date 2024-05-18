#pragma once
#include "RNSVGBaseComponentInstance.h"  
#include <math.h>  
#include "ShadowNodes.h"
#include "SvgPattern.h"

namespace rnoh {
namespace svg {
class RNSVGPatternComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGPatternShadowNode> {

 

public:
    RNSVGPatternComponentInstance(Context context);


      

      

     void UpdateElementProps(SharedConcreteProps const &props) override;

};

} // namespace svg
} // namespace rnoh