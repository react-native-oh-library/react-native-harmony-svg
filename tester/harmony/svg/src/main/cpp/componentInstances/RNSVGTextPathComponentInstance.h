#pragma once
#include "RNSVGBaseCI.h"    
#include "ShadowNodes.h"
#include "SvgTextPath.h"

namespace rnoh {
namespace svg {

class RNSVGTextPathComponentInstance : public RNSVGBaseCI<facebook::react::RNSVGTextPathShadowNode> {

private:
    std::shared_ptr<SvgTextPath> m_svgTP = std::make_shared<SvgTextPath>();

public:
    RNSVGTextPathComponentInstance(Context context);

    void UpdateSpecialProps(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh