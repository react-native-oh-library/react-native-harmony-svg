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
        mForeignStackNode.SetPointScaleFactor(getLayoutMetrics().pointScaleFactor);
        mForeignStackNode.SetSnapPosition(propsConversionValue(m_props->x), propsConversionValue(m_props->y));
        mForeignStackNode.SetSnapWidth(propsConversionValue(m_props->width));
        mForeignStackNode.SetSnapHeight(propsConversionValue(m_props->height));

        mForeignStackNode.SetClipPath(m_props->clipPath, m_props->clipRule);
        mForeignStackNode.SetMask(m_props->mask);
        mForeignStackNode.SetTransform(m_props->matrix);
        auto childs = getChildren();
        if (childs.size() > 0) {
            for (ComponentInstance::Shared c : childs) {
                if ((m_props->opacity > 0 && m_props->opacity != 1)) {
                    setOpacity(c->getLocalRootArkUINode(), m_props->opacity);
                }
            }
        }
        mForeignStackNode.SetGeneratedPixelMap(true);
    }
}

Dimension RNSVGForeignObjectComponentInstance::propsConversionValue(const folly::dynamic &d) {
    if (d.isNull()) {
        return Dimension(0, DimensionUnit::INVALID);
    }
    return StringUtils::StringToDimension(d.asString(), true);
}

void RNSVGForeignObjectComponentInstance::setOpacity(ArkUINode &node, float op) {
    if (op != 1) {
        node.setOpacity(m_props->opacity);
    }
}

void RNSVGForeignObjectComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                          std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
    float width = childComponentInstance->getLayoutMetrics().frame.size.width;
    float height = childComponentInstance->getLayoutMetrics().frame.size.height;
    mForeignStackNode.setNodeSize(width, height);
    node.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
}

void RNSVGForeignObjectComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
    CppComponentInstance::onChildRemoved(childComponentInstance);
}

SvgForeignObjectNode &RNSVGForeignObjectComponentInstance::getLocalRootArkUINode() { return mForeignStackNode; }


} // namespace svg
}