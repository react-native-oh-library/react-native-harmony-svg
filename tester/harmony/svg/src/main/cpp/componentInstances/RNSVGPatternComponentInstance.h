#pragma once

#include "RNSVGBaseComponentInstance.h"

namespace rnoh {
namespace svg {
class RNSVGPatternComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGPatternShadowNode> {

public:
    RNSVGPatternComponentInstance(Context context);

    void UpdateElementProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh