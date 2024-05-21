#pragma once
#include "RNSVGBaseComponentInstance.h"
#include "ShadowNodes.h"

namespace rnoh {
namespace svg {

class RNSVGRectComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGRectShadowNode> {


public:
    RNSVGRectComponentInstance(Context context);

    void UpdateElementProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh