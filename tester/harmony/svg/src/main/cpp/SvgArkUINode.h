/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgNode.h"
#include "SvgHost.h"
#include "RNOH/arkui/ArkUINode.h"
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
    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr;
    UserCallback *userCallback_ = nullptr;
    void (*eventReceiver)(ArkUI_NodeCustomEvent *event);

public:
    SvgArkUINode();
    ~SvgArkUINode() override;
	static ArkUI_NodeHandle CreateValidHandle();

    void SetSvgNode(const std::weak_ptr<SvgNode>& node)
    {
        root_ = node;
    }
    void ResetNodeHandle() {
        
    }
};

} // namespace svg
} // namespace rnoh