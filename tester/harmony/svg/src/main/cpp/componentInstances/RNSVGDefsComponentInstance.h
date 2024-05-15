#pragma once
#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"
#include "SvgDefs.h"

namespace rnoh {
namespace svg {

class RNSVGDefsComponentInstance : public CppComponentInstance<facebook::react::RNSVGDefsShadowNode>, public SvgHost {

private:
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGDefsComponentInstance(Context context);
    
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override{
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }
    
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override{}
    
    SvgArkUINode &getLocalRootArkUINode() override;
    
    void onPropsChanged(SharedConcreteProps const &props) override;
};

} // namespace svg
} // namespace rnoh