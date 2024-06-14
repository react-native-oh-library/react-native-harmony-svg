#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgShadowNodes.h"
#include "SvgDefs.h"

namespace rnoh {
namespace svg {

class RNSVGDefsComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGDefsShadowNode> {

public:
    RNSVGDefsComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
        SetSvgNode(std::make_shared<SvgDefs>());
    }
    
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {
        OnChildRemoveCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    void UpdateElementProps(SharedConcreteProps const &props) override {
        auto svgDefs = std::dynamic_pointer_cast<SvgDefs>(GetSvgNode());
        svgDefs->UpdateHrefRenderProps(props);
    }
};

} // namespace svg
} // namespace rnoh