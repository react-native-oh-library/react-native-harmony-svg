
#pragma once
#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include <math.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"
#include "SvgUse.h"

namespace rnoh {

class RNSVGUseComponentInstance : public CppComponentInstance<facebook::react::RNSVGUseShadowNode>, public SvgHost {

private:
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGUseComponentInstance(Context context);
    
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override{
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }
    
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override{}
    
    SvgArkUINode &getLocalRootArkUINode() override;
    
    void onPropsChanged(SharedConcreteProps const &props) override;
};
} // namespace rnoh