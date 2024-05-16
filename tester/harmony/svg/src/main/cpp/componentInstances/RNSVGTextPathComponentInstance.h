#pragma once
#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"
#include "SvgTextPath.h"

namespace rnoh {

class RNSVGTextPathComponentInstance : public CppComponentInstance<facebook::react::RNSVGTextPathShadowNode>,
                                       public SvgHost {

private:
    std::shared_ptr<SvgTextPath> m_svgTP = std::make_shared<SvgTextPath>();
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGTextPathComponentInstance(Context context);

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}

    SvgArkUINode &getLocalRootArkUINode() override {
        return m_svgArkUINode;
    }

    void onPropsChanged(SharedConcreteProps const &props) override;
};
} // namespace rnoh