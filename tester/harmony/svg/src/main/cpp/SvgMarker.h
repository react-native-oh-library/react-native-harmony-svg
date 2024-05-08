//
// Created on 2024/5/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGMARKER_H
#define HARMONY_SVGMARKER_H

#include "SvgGroup.h"
#include "properties/SvgMarkerPosition.h"
#include "properties/Dimension.h"
#include "properties/Size.h"
#include "Props.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <native_drawing/drawing_font_collection.h>
#include <native_drawing/drawing_register_font.h>
#include <native_drawing/drawing_text_declaration.h>
#include <native_drawing/drawing_text_typography.h>

namespace rnoh {

class SvgMarker : public SvgGroup {
public:
    SvgMarker() = default;
    ~SvgMarker() override = default;

    Size size;

    void setRefX(Dimension refX) {
        mRefX = ConvertDimensionToPx(refX, size, SvgLengthType::HORIZONTAL);
        invalidate();
    }

    void setRefY(Dimension refY) {
        mRefY = ConvertDimensionToPx(refY, size, SvgLengthType::VERTICAL);
        invalidate();
    }

    void setMarkerWidth(Dimension markerWidth) {
        mMarkerWidth = ConvertDimensionToPx(markerWidth, size, SvgLengthType::HORIZONTAL);
        invalidate();
    }

    void setMarkerHeight(Dimension markerHeight) {
        mMarkerHeight = ConvertDimensionToPx(markerHeight, size, SvgLengthType::VERTICAL);
        invalidate();
    }

    void setMarkerUnits(std::string markerUnits) {
        mMarkerUnits = markerUnits;
        invalidate();
    }

    void setOrient(std::string orient) {
        mOrient = orient;
        invalidate();
    }

    void setMinX(float minX) {
        mMinX = minX;
        invalidate();
    }

    void setMinY(float minY) {
        mMinY = minY;
        invalidate();
    }

    void setVbWidth(float vbWidth) {
        mVbWidth = vbWidth;
        invalidate();
    }

    void setVbHeight(float vbHeight) {
        mVbHeight = vbHeight;
        invalidate();
    }

    void setAlign(std::string align) {
        mAlign = align;
        invalidate();
    }

    void setMeetOrSlice(int meetOrSlice) {
        mMeetOrSlice = meetOrSlice;
        invalidate();
    }
    
    void invalidate();

    void renderMarker(OH_Drawing_Canvas *canvas, OH_Drawing_Pen *paint, float opacity, SvgMarkerPosition position, float strokeWidth);
    
    double relativeOnWidth(double markerWidth){
        return markerWidth;
    }
    
    double relativeOnHeight(double markerHeight){
        return markerHeight;
    }
    
private:
    OH_Drawing_Matrix* markerTransform;
    double mRefX;
    double mRefY;
    double mMarkerWidth;
    double mMarkerHeight;
    std::string mMarkerUnits;
    std::string mOrient;
    float mMinX;
    float mMinY;
    float mVbWidth;
    float mVbHeight;
    std::string mAlign;
    int mMeetOrSlice;
    int mScale;
    
};
} // namespace rnoh

#endif //HARMONY_SVGMARKER_H
