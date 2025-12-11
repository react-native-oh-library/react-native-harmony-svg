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
#include "properties/Dimension.h"

namespace rnoh {
namespace svg {
class SvgForeignObjectNode : public ArkUINode {
public:
    SvgForeignObjectNode();
    ~SvgForeignObjectNode() override;
    void onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) override;
    StackNode &getSnapNode() { return mStackNode; }
    void insertChild(ArkUINode &child, std::size_t index);
    void SetSnapPosition(Dimension x, Dimension y);
    void SetSnapWidth(Dimension width);
    void SetSnapHeight(Dimension height);
    void SetPointScaleFactor(float pointScaleFactor) {
        pointScaleFactor_ = pointScaleFactor;
    }
    void SetTransform(std::vector<double> transform) {
        transform_ = transform;
    }
    void setNodeSize(float w, float h){
        mStackNode.setSize({w, h});
    }
    OH_PixelmapNative *GetNodePixelMap();
    void SetForeignNodeDelegate(SvgForeignObjectNodeDelegate *delegate) { m_NodeDelegate = delegate; };
    void SetGeneratedPixelMap(bool isNeed) {
       _isGeneratedPixelMap = isNeed;
    }
    
    void SetClipPath(std::string path,int clipRule) {
        _path = path;
        _clipRule = clipRule;
    }
     void SetMask(std::string mask) {
        _mask = mask;
    }
    
private:
    StackNode mStackNode;
    SvgForeignObjectNodeDelegate *m_NodeDelegate;
    Dimension _width{0};
    Dimension _height{0};
    Dimension _positionX{0};
    Dimension _positionY{0};
    std::string _path{""};
    std::string _mask{""};
    std::vector<double> transform_;
    int _clipRule{0};
    float pointScaleFactor_{0};
    bool _isGeneratedPixelMap{false}; //防止快照生成多次，导致性能影响
};

} // namespace svg
} // namespace rnoh
#endif // HARMONY_SVGFOREIGNOBJECTNODE_H
