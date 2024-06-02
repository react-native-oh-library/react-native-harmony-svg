#pragma once

#include "RNSVGBaseComponentInstance.h"

namespace rnoh {
namespace svg {
class RNSVGSymbolComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGSymbolShadowNode> {

public:
    RNSVGSymbolComponentInstance(Context context);

    void UpdateElementProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh