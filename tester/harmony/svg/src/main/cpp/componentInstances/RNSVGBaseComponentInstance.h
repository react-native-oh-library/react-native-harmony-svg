#pragma once
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "SvgArkUINode.h"
#include "SvgHost.h"
namespace rnoh {
namespace svg {

template <typename T> class RNSVGBaseComponentInstance : public CppComponentInstance<T>, public SvgHost {
public:
    RNSVGBaseComponentInstance(ComponentInstance::Context context) : CppComponentInstance<T>(std::move(context)) {}

    void onPropsChanged(typename CppComponentInstance<T>::SharedConcreteProps const &props) override {
        GetSvgNode()->UpdateCommonProps(props);
        UpdateSpecialProps(props);
    }
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }
    
    void setLayout(facebook::react::LayoutMetrics layoutMetrics) override {};

protected:
    virtual void UpdateSpecialProps(typename CppComponentInstance<T>::SharedConcreteProps const &props) = 0;
    SvgArkUINode &getLocalRootArkUINode() override { return *m_svgArkUINode.lock().get(); }

private:
    std::weak_ptr<SvgArkUINode> m_svgArkUINode;
};

} // namespace svg
} // namespace rnoh