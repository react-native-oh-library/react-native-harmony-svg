#pragma once
#include "SvgNode.h"
#include "RNOH/arkui/ArkUINode.h"
#include "arkui/native_node.h"

namespace rnoh {

struct UserCallback {
    std::function<void(ArkUI_NodeCustomEvent *event)> callback;
};

// ArkUINode
class SvgArkUINode : public ArkUINode {
private:
    void OnDraw(ArkUI_NodeCustomEvent *event);
    
    std::shared_ptr<SvgNode> root_;
    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr;
    UserCallback *userCallback_ = nullptr;

public:
    SvgArkUINode();
    ~SvgArkUINode() override;

    void SetSvgNode(const std::shared_ptr<SvgNode>& node)
    {
        root_ = node;
    }
    void ResetNodeHandle() {
        
    }
};
} // namespace rnoh