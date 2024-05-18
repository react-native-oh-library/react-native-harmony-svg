#pragma once
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "SvgArkUINode.h"
#include "SvgHost.h"
#include "RNSVGSvgViewComponentInstance.h"

namespace rnoh {
namespace svg {

template <typename T> class RNSVGBaseComponentInstance : public CppComponentInstance<T>, public SvgHost {
public:
    RNSVGBaseComponentInstance(ComponentInstance::Context context) : CppComponentInstance<T>(std::move(context)) {}

    void onPropsChanged(typename CppComponentInstance<T>::SharedConcreteProps const &props) override {
        GetSvgNode()->UpdateCommonProps(props);
        UpdateElementProps(props);
        svgMarkDirty();
    }
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }
    
    void setLayout(facebook::react::LayoutMetrics layoutMetrics) override {};
    
    std::shared_ptr<RNSVGSvgViewComponentInstance> getParentSvgView() {
        auto parent = CppComponentInstance<T>::getParent().lock();
        while (parent) {
            auto svgView = std::dynamic_pointer_cast<RNSVGSvgViewComponentInstance>(parent);
            if (svgView) {
                return svgView;
            }
            parent = parent->getParent().lock();
        }
        return nullptr;
    }
    
    void svgMarkDirty() {
        auto svgView = m_svgViewComponentInstance.lock();
        if (svgView == nullptr) {
            svgView = getParentSvgView();
        }
        if (svgView != nullptr) {
            m_svgViewComponentInstance = svgView;
            svgView->getLocalRootArkUINode().markDirty();
        }
    }

protected:
    virtual void UpdateElementProps(typename CppComponentInstance<T>::SharedConcreteProps const &props) = 0;
    SvgArkUINode &getLocalRootArkUINode() override { return getParentSvgView()->getLocalRootArkUINode(); }

private:
    std::weak_ptr<RNSVGSvgViewComponentInstance> m_svgViewComponentInstance;
};

} // namespace svg
} // namespace rnoh