#pragma once
#include "RNSVGBaseCI.h"  
#include <math.h>  
#include "ShadowNodes.h"
#include "SvgPattern.h"

namespace rnoh {
namespace svg {
class RNSVGPatternComponentInstance : public RNSVGBaseCI<facebook::react::RNSVGPatternShadowNode> {

 

public:
    RNSVGPatternComponentInstance(Context context);


      

      

     void UpdateSpecialProps(SharedConcreteProps const &props) override;

};

} // namespace svg
} // namespace rnoh