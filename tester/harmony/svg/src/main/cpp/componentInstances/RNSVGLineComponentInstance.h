#pragma once
#include "RNSVGBaseCI.h"  
#include <math.h>  
#include "ShadowNodes.h"
#include "SvgLine.h"

namespace rnoh {
namespace svg {

class RNSVGLineComponentInstance : public RNSVGBaseCI<facebook::react::RNSVGLineShadowNode> {

 

public:
    RNSVGLineComponentInstance(Context context);

    

      

      

     void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh