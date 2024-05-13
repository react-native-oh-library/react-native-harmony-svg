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
namespace rnoh{
    class SvgSymbol : public SvgGraphic{
    public:
        SvgSymbol() = default;
        ~SvgSymbol() override = default;
        float mMinX;
        float mMinY;
        float mVbWidth;
        float mVbHeight;
        std::string mAlign;
        int mMeetOrSlice;
        void InitDefsFlag();
        void drawSymbol(OH_Drawing_Canvas *canvas, float width, float height);
    };
}
#endif //HARMONY_SVGSYMBOL_H
