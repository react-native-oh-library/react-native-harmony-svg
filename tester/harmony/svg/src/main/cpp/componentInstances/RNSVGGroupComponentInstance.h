#pragma once

#include "RNSVGBaseComponentInstance.h"    
#include "ShadowNodes.h"
#include "SvgGroup.h"

namespace rnoh {
namespace svg {
class RNSVGGroupComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGGroupShadowNode> {


public:
    RNSVGGroupComponentInstance(Context context);
    
    void UpdateElementProps(SharedConcreteProps const &props) override;

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {
        OnChildRemoveCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }
};

} // namespace svg
} // namespace rnoh