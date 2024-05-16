#pragma once
#include "RNSVGBaseCI.h"
#include <math.h>
#include "ShadowNodes.h"
#include "SvgRect.h"

namespace rnoh {
namespace svg {

class RNSVGRectComponentInstance : public RNSVGBaseCI<facebook::react::RNSVGRectShadowNode> {


public:
    RNSVGRectComponentInstance(Context context);

    void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh