#pragma once

#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"

namespace rnoh {
namespace svg {

class RNSVGSvgViewComponentInstance : public CppComponentInstance<facebook::react::RNSVGSvgViewShadowNode>,
                                      public SvgHost {
private:
    SvgArkUINode m_svgArkUINode;

public:
    RNSVGSvgViewComponentInstance(Context context);

    // get SvgNode from childComponentInstance and set it to root_
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    // TODO get SvgNode and delete it from svg tree
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {
        OnChildRemoveCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    SvgArkUINode &getLocalRootArkUINode() override;

    void onPropsChanged(SharedConcreteProps const &props) override;

    // since we can't get color correctly from props
    std::optional<std::string> getColorFromDynamic(folly::dynamic value);

    bool canHandleTouch() const override {
        if (m_props != nullptr) {
            auto props = std::dynamic_pointer_cast<const facebook::react::RNSVGSvgViewProps>(m_props);
            return props->pointerEvents == "auto" || props->pointerEvents == "box-only" ||
                   props->pointerEvents.size() == 0;
        }
        return true;
    };

    bool canChildrenHandleTouch() const override {
        if (m_props != nullptr) {
            auto props = std::dynamic_pointer_cast<const facebook::react::RNSVGSvgViewProps>(m_props);
            return props->pointerEvents == "auto" || props->pointerEvents == "box-none" ||
                   props->pointerEvents.size() == 0;
        }
        return true;
    };
};

} // namespace svg
} // namespace rnoh