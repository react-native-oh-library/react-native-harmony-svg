//
// Created on 2025/10/17.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SvgForeignObjectNode.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include <deviceinfo.h>
#include <info/application_target_sdk_version.h>

namespace rnoh {
namespace svg {
SvgForeignObjectNode::SvgForeignObjectNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK)) {
    mStackNode.setVisibility(ArkUI_Visibility::ARKUI_VISIBILITY_HIDDEN);
    mStackNode.setClip(true);
    maybeThrow(NativeNodeApi::getInstance()->addChild(m_nodeHandle, mStackNode.getArkUINodeHandle()));
}

SvgForeignObjectNode::~SvgForeignObjectNode() {
    if (m_NodeDelegate) {
        m_NodeDelegate = nullptr;
    }
    _isGeneratedPixelMap = false;	
}
void SvgForeignObjectNode::insertChild(ArkUINode &child, std::size_t index) { mStackNode.insertChild(child, index); }

void SvgForeignObjectNode::SetSnapHeight(float height) { _height = height; }

void SvgForeignObjectNode::SetSnapWidth(float width) { _width = width; }

void SvgForeignObjectNode::SetSnapPosition(float x, float y) {
    _positionX = x;
    _positionY = y;
}

void SvgForeignObjectNode::onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) {
    if (eventType == ArkUI_NodeEventType::NODE_EVENT_ON_AREA_CHANGE) {
        if (m_NodeDelegate && _isGeneratedPixelMap) {
            OH_PixelmapNative *pixelMap = GetNodePixelMap();
            if (!pixelMap) {
                LOG(ERROR) << "[svgForeignNode] get node snapshot pixelMap is null";
                return;
            }
            _isGeneratedPixelMap = false;
            m_NodeDelegate->onDrawForeignImage(pixelMap, _width, _height, _positionX, _positionY);
        }
    }
}

OH_PixelmapNative *SvgForeignObjectNode::GetNodePixelMap() {
#ifdef OH_CURRENT_API_VERSION
    if (OH_CURRENT_API_VERSION < 15 || OH_GetSdkApiVersion() < 15) {
        LOG(ERROR) << "[svgForeignNode] current sdk or rom cannot support ForeignObject";
        return nullptr;
    }
    OH_PixelmapNative *pixelMap;
    ArkUI_SnapshotOptions *options = OH_ArkUI_CreateSnapshotOptions();
    OH_ArkUI_SnapshotOptions_SetScale(options, 1);
    int32_t code = OH_ArkUI_GetNodeSnapshot(mStackNode.getArkUINodeHandle(), options, &pixelMap);
    if (code == ARKUI_ERROR_CODE_NO_ERROR) {
        return pixelMap;
    }
#endif
    return nullptr;
}

} // namespace svg
} // namespace rnoh
