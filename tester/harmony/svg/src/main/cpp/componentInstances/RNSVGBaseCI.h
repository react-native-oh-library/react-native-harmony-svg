#pragma once
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "SvgArkUINode.h"
#include "SvgHost.h"
namespace rnoh::svg {
template <typename T> class RNSVGBaseCI : public CppComponentInstance<T>, public SvgHost {
public:
    RNSVGBaseCI(ComponentInstance::Context context) : CppComponentInstance<T>(std::move(context)) {}

    void onPropsChanged(typename CppComponentInstance<T>::SharedConcreteProps const &props) override {
        CppComponentInstance<T>::onPropsChanged(props);
        if (!props->responsible) {
            m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::None);
        } else {
            m_svgArkUINode.setHitTestMode(facebook::react::PointerEventsMode::Auto);
        }

        GetSvgNode()->UpdateCommonProps(props);
        UpdateSpecialProps(props);
    }
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

protected:
    virtual void UpdateSpecialProps(typename CppComponentInstance<T>::SharedConcreteProps const &props) = 0;
    SvgArkUINode &getLocalRootArkUINode() override { return m_svgArkUINode; }

private:
    SvgArkUINode m_svgArkUINode;
};
} // namespace rnoh