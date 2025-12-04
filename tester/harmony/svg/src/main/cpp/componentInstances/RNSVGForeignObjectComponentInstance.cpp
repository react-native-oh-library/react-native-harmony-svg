//
// Created on 2025/10/16.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RNSVGForeignObjectComponentInstance.h"
namespace rnoh {
namespace svg {

RNSVGForeignObjectComponentInstance::RNSVGForeignObjectComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
    DLOG(INFO) << "RNSVGForeignObjectComponentInstance";
    NativeNodeApi::getInstance()->registerNodeEvent(mForeignStackNode.getArkUINodeHandle(), NODE_EVENT_ON_AREA_CHANGE,
                                                    NODE_EVENT_ON_AREA_CHANGE, this);
    mForeignStackNode.insertChild(node, 0);
}


RNSVGForeignObjectComponentInstance::~RNSVGForeignObjectComponentInstance() {
    NativeNodeApi::getInstance()->unregisterNodeEvent(mForeignStackNode.getArkUINodeHandle(), NODE_EVENT_ON_AREA_CHANGE);
}

void RNSVGForeignObjectComponentInstance::onFinalizeUpdates() {
    ComponentInstance::onFinalizeUpdates();
    if (m_props) {
        float pointScaleFactor = getLayoutMetrics().pointScaleFactor;
        mForeignStackNode.SetSnapPosition(pointScaleFactor * std::stof(m_props->x),
                                          pointScaleFactor * std::stof(m_props->y));
        mForeignStackNode.SetSnapWidth(pointScaleFactor * std::stof(m_props->width));
        mForeignStackNode.SetSnapHeight(pointScaleFactor * std::stof(m_props->height));
        mForeignStackNode.SetClipPath(m_props->clipPath, m_props->clipRule);
        mForeignStackNode.SetMask(m_props->mask);
        
        auto childs = getChildren();
        if (childs.size() > 0) {
            for (ComponentInstance::Shared c : childs) {
                if ((m_props->opacity > 0 && m_props->opacity != 1)) {
                    setOpacity(c->getLocalRootArkUINode(), m_props->opacity);
                }
                transform(c->getLocalRootArkUINode());
            }
        }
        mForeignStackNode.SetGeneratedPixelMap(true);
    }
}

void RNSVGForeignObjectComponentInstance::transform(ArkUINode &node) {
    // matrix 6 -> 16 ,2d->3d
    if (m_props->matrix.size() != 6) {
        return;
    }
    std::array<ArkUI_NumberValue, 16> transformValue;
    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 1) {
            transformValue[i] = {.f32 = static_cast<float>(m_props->matrix[i])};
        } else if (i == 4) {
            transformValue[i] = {.f32 = static_cast<float>(m_props->matrix[2])};
        } else if (i == 5) {
            transformValue[i] = {.f32 = static_cast<float>(m_props->matrix[3])};
        } else if (i == 10 || i == 15) {
            transformValue[i] = {.f32 = static_cast<float>(1)};
        } else if (i == 12) {
            transformValue[i] = {.f32 = static_cast<float>(m_props->matrix[4])};
        } else if (i == 13) {
            transformValue[i] = {.f32 = static_cast<float>(m_props->matrix[5])};
        } else {
            transformValue[i] = {.f32 = static_cast<float>(0)};
        }
    }
    ArkUI_AttributeItem transformItem = {transformValue.data(), transformValue.size()};
    NativeNodeApi::getInstance()->setAttribute(node.getArkUINodeHandle(), NODE_TRANSFORM, &transformItem);
}

void RNSVGForeignObjectComponentInstance::setOpacity(ArkUINode &node, float op) {
    if (op != 1) {
        node.setOpacity(m_props->opacity);
    }
}

void RNSVGForeignObjectComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                          std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
    node.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
}

void RNSVGForeignObjectComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
    CppComponentInstance::onChildRemoved(childComponentInstance);
}

SvgForeignObjectNode &RNSVGForeignObjectComponentInstance::getLocalRootArkUINode() { return mForeignStackNode; }


} // namespace svg
}