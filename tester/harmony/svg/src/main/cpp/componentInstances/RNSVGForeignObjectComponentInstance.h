//
// Created on 2025/10/16.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RNSVG_FOREIGN_OBJECT_COMPONENT_INSTANCE_H
#define RNSVG_FOREIGN_OBJECT_COMPONENT_INSTANCE_H
#include "RNOH/CppComponentInstance.h"
#include "SvgForeignObjectNode.h"
#include <react/renderer/components/react_native_svg/ShadowNodes.h>
#include "RNOH/arkui/ColumnNode.h"
namespace rnoh {
namespace svg {
class RNSVGForeignObjectComponentInstance : public CppComponentInstance<facebook::react::RNSVGForeignObjectShadowNode> {
public:
    RNSVGForeignObjectComponentInstance(Context context);
    ~RNSVGForeignObjectComponentInstance();

    void onFinalizeUpdates() override;
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

    SvgForeignObjectNode &getLocalRootArkUINode() override;

private:
    SvgForeignObjectNode mForeignStackNode;
    ColumnNode node;
};
} // namespace svg
} // namespace rnoh
#endif // RNSVG_FOREIGN_OBJECT_COMPONENT_INSTANCE_H
