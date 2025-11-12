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
        mForeignStackNode.SetGeneratedPixelMap(true);		
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