//
// Created on 2024/5/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SvgMarker.h"
#include "properties/Rect.h"
#include "properties/ViewBox.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

namespace rnoh {

    void SvgMarker::renderMarker(OH_Drawing_Canvas *canvas, const SvgMarkerPosition& position, float strokeWidth){
        LOG(INFO) << "[SvgMarker] renderMarker start";
        saveAndSetupCanvas(canvas, mCTM);
        const auto count = OH_Drawing_CanvasGetSaveCount(canvas);
    
        if(markerTransform == nullptr) {
            markerTransform = OH_Drawing_MatrixCreate();
        }else {
            OH_Drawing_MatrixDestroy(markerTransform);
            markerTransform = OH_Drawing_MatrixCreate();
        }
        Point origin = position.origin;
        OH_Drawing_MatrixTranslate(markerTransform, static_cast<float>(origin.x), static_cast<float>(origin.y));
        double markerAngle = (mOrient == "auto") ? -1 : std::atof(mOrient.c_str());
        float degrees = 180 + (markerAngle == -1 ? position.angle : static_cast<float>(markerAngle));
        
        LOG(INFO) << "[SvgMarker] renderMarker markerAngle=" << markerAngle << " degrees=" << degrees << " origin.x=" << origin.x << " origin.y=" << origin.y;
        OH_Drawing_MatrixPreRotate(markerTransform, degrees, static_cast<float>(origin.x), static_cast<float>(origin.y));

        if(mMarkerUnits == "strokeWidth"){
            OH_Drawing_MatrixPreScale(markerTransform, strokeWidth / mScale, strokeWidth / mScale, static_cast<float>(origin.x), static_cast<float>(origin.y));
        }
        double width = relativeOnWidth(mMarkerWidth) / mScale;
        double height = relativeOnHeight(mMarkerHeight) / mScale;
        Rect eRect(0, 0, static_cast<float>(width), static_cast<float>(height));
        LOG(INFO) << "[SvgMarker] renderMarker width=" << width << " height=" << height;
        if(!mAlign.empty()){
            Rect vbRect(mMinX * mScale, mMinY * mScale, (mMinX + mVbWidth) * mScale, (mMinY + mVbHeight) * mScale);
            OH_Drawing_Matrix* viewBoxMatrix = rhon::ViewBox::getTransform(vbRect, eRect, mAlign, mMeetOrSlice);
            float sx = OH_Drawing_MatrixGetValue(viewBoxMatrix, 0);
            float sy = OH_Drawing_MatrixGetValue(viewBoxMatrix, 4);
            OH_Drawing_MatrixPreScale(markerTransform, sx, sy, static_cast<float>(origin.x), static_cast<float>(origin.y));
        }
    
        double x = relativeOnWidth(mRefX);
        double y = relativeOnHeight(mRefY);
        LOG(INFO) << "[SvgMarker] renderMarker x=" << x << " y=" << y;
        OH_Drawing_MatrixPreTranslate(markerTransform, static_cast<float>(-x), static_cast<float>(-y));
        OH_Drawing_CanvasConcatMatrix(canvas, markerTransform);
        
        //todo 调用父类方法，未移植
        //drawGroup(canvas, paint, opacity);
        OnDrawTraversed(canvas);
    
        OH_Drawing_CanvasRestoreToCount(canvas, count);
        LOG(INFO) << "[SvgMarker] renderMarker done.";
    }
}