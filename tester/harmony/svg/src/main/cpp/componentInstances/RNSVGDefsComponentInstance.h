#pragma once
#include "RNSVGBaseComponentInstance.h"
#include "RNOH/CppComponentInstance.h"
#include "RNSVGBaseComponentInstance.h"
#include <folly/dynamic.h>  
#include "ShadowNodes.h"
#include "SvgDefs.h"

namespace rnoh {
namespace svg {

class RNSVGDefsComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGDefsShadowNode> {

public:
    RNSVGDefsComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
        SetSvgNode(std::make_shared<SvgDefs>());
    }

    void UpdateElementProps(SharedConcreteProps const &props) override {}
};

} // namespace svg
} // namespace rnoh