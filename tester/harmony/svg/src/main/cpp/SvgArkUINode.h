/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNOH/arkui/ArkUINode.h"
#include "SvgForeignObjectNodeDelegate.h"
#include "SvgHost.h"
#include "SvgNode.h"
#include "arkui/native_node.h"

namespace rnoh {
namespace svg {

struct UserCallback {
    std::function<void(ArkUI_NodeCustomEvent *event)> callback;
};

// ArkUINode
class SvgArkUINode : public ArkUINode {
private:
    void OnDraw(ArkUI_NodeCustomEvent *event);

    std::weak_ptr<SvgNode> root_;
    std::weak_ptr<SvgNode> _groupNode;
    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr;
    UserCallback *userCallback_ = nullptr;
    void (*eventReceiver)(ArkUI_NodeCustomEvent *event);

    std::vector<ForeignProps> foreignPropsArray;

public:
    SvgArkUINode();
    ~SvgArkUINode() override;
    static ArkUI_NodeHandle CreateValidHandle();
    void SetSvgNode(const std::weak_ptr<SvgNode> &node) { root_ = node; }
    void SetGroupNode(const std::weak_ptr<SvgNode> &node) { _groupNode = node; }
    void ResetNodeHandle() {}
    void AddChild(ArkUINode &node);
    void SetForeignObject(OH_PixelmapNative *pixelMap, float w, float h, float x, float y) {
        ForeignProps foreignProps = {std::move(pixelMap), w, h, x, y};
        if (auto groupNode = _groupNode.lock()) {
            groupNode->SetForeignObject(std::move(foreignProps));
        }
    }
};

} // namespace svg
} // namespace rnoh