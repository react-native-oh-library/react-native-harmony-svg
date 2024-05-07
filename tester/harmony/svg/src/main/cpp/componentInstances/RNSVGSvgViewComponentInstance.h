#pragma once

#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"

namespace rnoh {
class RNSVGSvgViewComponentInstance : public CppComponentInstance<facebook::react::RNSVGSvgViewShadowNode>,
                                      public SvgHost {
private:
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGSvgViewComponentInstance(Context context);

    // get SvgNode from childComponentInstance and set it to root_
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        auto childSvgHost = std::dynamic_pointer_cast<SvgHost>(childComponentInstance);
        if (childSvgHost) {
            GetSvgNode()->AppendChild(childSvgHost->GetSvgNode());
        }
    }
    
    // TODO get SvgNode and delete it from svg tree
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}
    
    SvgArkUINode &getLocalRootArkUINode() override;
    
    void onPropsChanged(SharedConcreteProps const &props) override;
};
} // namespace rnoh