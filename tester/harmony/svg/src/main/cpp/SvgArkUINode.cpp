/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SvgArkUINode.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include "SvgViewManager.h"
#include "arkui/native_node.h"
#include "arkui/native_type.h"
#include <functional>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_pen.h>
#include <native_drawing/drawing_types.h>
#include <sstream>

namespace rnoh {
namespace svg {

constexpr int NODE_EVENT_ID = 77;

// 对应SVGArkUINode
SvgArkUINode::SvgArkUINode() : ArkUINode(CreateValidHandle()) {

    userCallback_ = new UserCallback();
    // 设置自定义回调。注册onDraw
    userCallback_->callback = [this](ArkUI_NodeCustomEvent *event) {
        auto type = OH_ArkUI_NodeCustomEvent_GetEventType(event);
        switch (type) {
        case ARKUI_NODE_CUSTOM_EVENT_ON_DRAW:
            OnDraw(event);
            break;
        default:
            break;
        }
    };
    eventReceiver = [](ArkUI_NodeCustomEvent *event) {
        if (OH_ArkUI_NodeCustomEvent_GetEventTargetId(event) == NODE_EVENT_ID) {
            auto *userData = reinterpret_cast<UserCallback *>(OH_ArkUI_NodeCustomEvent_GetUserData(event));
            if (userData != nullptr && userData->callback != nullptr) {
                userData->callback(event);
            }
        }
    };
    maybeThrow(NativeNodeApi::getInstance()->addNodeCustomEventReceiver(m_nodeHandle, eventReceiver));
    maybeThrow(NativeNodeApi::getInstance()->registerNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW,
                                                                     NODE_EVENT_ID, userCallback_));
}

ArkUI_NodeHandle SvgArkUINode::CreateValidHandle() {
    auto handle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_CUSTOM);
    if (!handle) {
        return {};
    }
    return handle;
}

SvgArkUINode::~SvgArkUINode() {
    NativeNodeApi::getInstance()->removeNodeCustomEventReceiver(m_nodeHandle, eventReceiver);
    NativeNodeApi::getInstance()->unregisterNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    delete userCallback_;
    userCallback_ = nullptr;
}

void SvgArkUINode::AddChild(ArkUINode &node) {
    maybeThrow(NativeNodeApi::getInstance()->addChild(m_nodeHandle, node.getArkUINodeHandle()));
}
void SvgArkUINode::OnDraw(ArkUI_NodeCustomEvent *event) {
    auto *drawContext = OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(event);
    auto *drawingHandle = reinterpret_cast<OH_Drawing_Canvas *>(OH_ArkUI_DrawContext_GetCanvas(drawContext));
    DLOG(INFO) << "[svg] <SVGArkUINode> CanvasGetHeight: " << OH_Drawing_CanvasGetHeight(drawingHandle);
    DLOG(INFO) << "[svg] <SVGArkUINode> CanvasGetWidth: " << OH_Drawing_CanvasGetWidth(drawingHandle);
    auto root = root_.lock();
    CHECK_NULL_VOID(root);
    if (root->GetContext()) {
        // reset the idMap
        root->GetContext()->ClearIdMap();
    }
    root->ContextTraversal();
    root->InitStyle({});
    root->Draw(drawingHandle);
}

} // namespace svg
} // namespace rnoh
