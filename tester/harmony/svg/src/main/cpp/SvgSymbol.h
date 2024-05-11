//
// Created on 2024/5/10.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGSYMBOL_H
#define HARMONY_SVGSYMBOL_H
#include "SvgGraphic.h"
#include "properties/ViewBox.h"
namespace rnoh {


class SvgSymbol : public SvgGraphic {

public:
    SvgSymbol(std::shared_ptr<SvgNode> p1) {}
    SvgSymbol() = default;
    ~SvgSymbol() override = default;
    float mMinX;
    float mMinY;
    float mVbWidth;
    float mVbHeight;
    std::string mAlign;
    int mMeetOrSlice;

    void drawSymbol(OH_Drawing_Canvas *canvas, float width, float height) {
        LOG(INFO) << "[SvgUse::SvgSymbol] : drawSymbol width :<< "<< width << " height:"<< height << "mAlign.empty()" << mAlign.empty();
        if (!mAlign.empty()) {
            LOG(INFO) << "[SvgUse::SvgSymbol] : drawSymbol start" ;
            Rect vbRect(mMinX * scale_, mMinY * scale_, (mMinX + mVbWidth) * scale_, (mMinY + mVbHeight) * scale_);
            Rect eRect(0, 0, width, height);
            OH_Drawing_Matrix *viewBoxMatrix = rhon::ViewBox::getTransform(vbRect, eRect, mAlign, mMeetOrSlice);
            OH_Drawing_CanvasConcatMatrix(canvas, viewBoxMatrix);
        }
    }
};
} // namespace rnoh
#endif // HARMONY_SVGSYMBOL_H
