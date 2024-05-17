#pragma once
#include "RNSVGBaseComponentInstance.h"
#include <math.h>
#include "ShadowNodes.h"
#include "SvgRect.h"

namespace rnoh {
namespace svg {

class RNSVGRectComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGRectShadowNode> {


public:
    RNSVGRectComponentInstance(Context context);

    void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh