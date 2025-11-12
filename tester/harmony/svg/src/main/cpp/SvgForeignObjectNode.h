//
// Created on 2025/10/17.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGFOREIGNOBJECTNODE_H
#define HARMONY_SVGFOREIGNOBJECTNODE_H
#include "RNOH/arkui/ArkUINode.h"
#include "RNOH/arkui/StackNode.h"
#include "SvgForeignObjectNodeDelegate.h"

namespace rnoh {
namespace svg {
class SvgForeignObjectNode : public ArkUINode {
public:
    SvgForeignObjectNode();
    ~SvgForeignObjectNode() override;
    void onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) override;
    StackNode &getSnapNode() { return mStackNode; }
    void insertChild(ArkUINode &child, std::size_t index);
    void SetSnapPosition(float x, float y);
    void SetSnapWidth(float width);
    void SetSnapHeight(float height);
    OH_PixelmapNative *GetNodePixelMap();
    void SetForeignNodeDelegate(SvgForeignObjectNodeDelegate *delegate) { m_NodeDelegate = delegate; };
    void SetGeneratedPixelMap(bool isNeed) {
       _isGeneratedPixelMap = isNeed;
    }

private:
    StackNode mStackNode;
    SvgForeignObjectNodeDelegate *m_NodeDelegate;
    float _width{0};
    float _height{0};
    float _positionX{0};
    float _positionY{0};
    bool _isGeneratedPixelMap{false}; //防止快照生成多次，导致性能影响
};

} // namespace svg
} // namespace rnoh
#endif // HARMONY_SVGFOREIGNOBJECTNODE_H
