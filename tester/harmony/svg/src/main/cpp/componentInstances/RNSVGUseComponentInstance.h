
#pragma once
#include "RNSVGBaseComponentInstance.h"  
#include <math.h>  
#include "ShadowNodes.h"
#include "SvgUse.h"

namespace rnoh {
namespace svg {

class RNSVGUseComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGUseShadowNode> {
public:
    RNSVGUseComponentInstance(Context context);
    void UpdateElementProps(SharedConcreteProps const &props) override;
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        LOG(INFO) << "[RNSvgUseComponentInstance] onChildInserted";
    }
};

} // namespace svg
} // namespace rnoh