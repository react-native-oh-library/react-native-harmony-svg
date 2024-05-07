#pragma once
#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include <math.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"
#include "SvgLine.h"

namespace rnoh {

class RNSVGLineComponentInstance : public CppComponentInstance<facebook::react::RNSVGLineShadowNode>, public SvgHost {

private:
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGLineComponentInstance(Context context);

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {}

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}

    SvgArkUINode &getLocalRootArkUINode() override;

    void onPropsChanged(SharedConcreteProps const &props) override;
};
} // namespace rnoh