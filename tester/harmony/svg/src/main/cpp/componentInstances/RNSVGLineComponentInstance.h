#pragma once
#include "RNSVGBaseComponentInstance.h"  
#include <math.h>  
#include "ShadowNodes.h"
#include "SvgLine.h"

namespace rnoh {
namespace svg {

class RNSVGLineComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGLineShadowNode> {

 

public:
    RNSVGLineComponentInstance(Context context);

    

      

      

     void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh