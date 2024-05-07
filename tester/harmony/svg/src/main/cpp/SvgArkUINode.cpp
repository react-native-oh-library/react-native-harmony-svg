#include <functional>

#include "arkui/native_interface.h"
#include "arkui/native_node.h"
#include "arkui/native_type.h"
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_pen.h>
#include <native_drawing/drawing_types.h>
#include "SvgArkUINode.h"
#include <sstream>

namespace rnoh {
namespace {

class ArkUI_NativeModule {
public:
    ArkUI_NativeModule() {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeApi_);
        nodeApi_->registerNodeCustomEventReceiver([](ArkUI_NodeCustomEvent *event) {
            auto *userData = reinterpret_cast<UserCallback *>(OH_ArkUI_NodeCustomEvent_GetUserData(event));
            userData->callback(event);
        });
    }
    ~ArkUI_NativeModule() { nodeApi_->unregisterNodeCustomEventReceiver(); }
    static ArkUI_NativeModule *GetInstance() {
        static ArkUI_NativeModule nativeModule;
        return &nativeModule;
    }
    ArkUI_NativeNodeAPI_1 *GetNodeAPI() { return nodeApi_; }

private:
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;
};
} // namespace

// 对应SVGArkUINode
SvgArkUINode::SvgArkUINode()
    : ArkUINode(ArkUI_NativeModule::GetInstance()->GetNodeAPI()->createNode(ARKUI_NODE_CUSTOM)) {
    nativeModule_ = ArkUI_NativeModule::GetInstance()->GetNodeAPI();
    userCallback_ = new UserCallback();
    // 设置自定义回调。注册onDraw
    userCallback_->callback = [this](ArkUI_NodeCustomEvent *event) {
        auto type = OH_ArkUI_NodeCustomEvent_GetEventType(event);
        LOG(INFO) << "type" << type;
        switch (type) {
        case ARKUI_NODE_CUSTOM_EVENT_ON_DRAW:
            OnDraw(event);
            break;
        default:
            break;
        }
    };
    //
    nativeModule_->registerNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW, 0, userCallback_);
}
SvgArkUINode::~SvgArkUINode() {
    nativeModule_->unregisterNodeCustomEvent(m_nodeHandle, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    delete userCallback_;
}

void SvgArkUINode::OnDraw(ArkUI_NodeCustomEvent *event) {
    //
    auto *drawContext = OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(event);
    auto *drawingHandle = reinterpret_cast<OH_Drawing_Canvas *>(OH_ArkUI_DrawContext_GetCanvas(drawContext));
    LOG(INFO) << "[svg] <SVGArkUINode> CanvasGetHeight: " << OH_Drawing_CanvasGetHeight(drawingHandle) / 3.25010318;
    LOG(INFO) << "[svg] <SVGArkUINode> CanvasGetWidth: " << OH_Drawing_CanvasGetWidth(drawingHandle) / 3.25010318;
    root_->Draw(drawingHandle);
}

}; // namespace rnoh
