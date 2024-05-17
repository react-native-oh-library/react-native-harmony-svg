#pragma once

//
// Created on 2024/5/12.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGSYMBOL_H
#define HARMONY_SVGSYMBOL_H
#include "SvgGraphic.h"
#include "properties/ViewBox.h"
namespace rnoh {
namespace svg {

class SvgSymbol : public SvgGraphic {
public:
    SvgSymbol() : SvgGraphic() { InitSymbolFlag(); }
    ~SvgSymbol() override = default;

    void InitSymbolFlag() {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }
    float mMinX = 0.0f;
    float mMinY = 0.0f;
    float mVbWidth = 0.0f;
    float mVbHeight = 0.0f;
    std::string mAlign;
    int mMeetOrSlice = -1;
    void InitDefsFlag();
    void drawSymbol(OH_Drawing_Canvas *canvas, float width, float height);
};

} // namespace svg
} // namespace rnoh
#endif // HARMONY_SVGSYMBOL_H
