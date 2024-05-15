#pragma once
#include "RNOH/CppComponentInstance.h"
// #include "SwiperNode.h"
// #include "EventEmitters.h"
#include <folly/dynamic.h>
#include <math.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"
#include "SvgSymbol.h"

namespace rnoh {
namespace svg {
class RNSVGSymbolComponentInstance : public CppComponentInstance<facebook::react::RNSVGSymbolShadowNode>, public SvgHost {

private:
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGSymbolComponentInstance(Context context);

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override{}

    SvgArkUINode &getLocalRootArkUINode() override;

    void onPropsChanged(SharedConcreteProps const &props) override;

};

} // namespace svg
} // namespace rnoh