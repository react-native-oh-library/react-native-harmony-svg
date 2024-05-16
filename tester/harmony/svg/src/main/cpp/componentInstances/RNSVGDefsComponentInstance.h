#pragma once
#include "RNSVGBaseCI.h"
#include "RNOH/CppComponentInstance.h"
#include "RNSVGBaseCI.h"
#include <folly/dynamic.h>  
#include "ShadowNodes.h"
#include "SvgDefs.h"

namespace rnoh {
namespace svg {

class RNSVGDefsComponentInstance : public RNSVGBaseCI<facebook::react::RNSVGDefsShadowNode> {

public:
    RNSVGDefsComponentInstance(Context context) : RNSVGBaseCI(std::move(context)) {
        SetSvgNode(std::make_shared<SvgDefs>());
    }

    void UpdateSpecialProps(SharedConcreteProps const &props) override {}
};

} // namespace svg
} // namespace rnoh