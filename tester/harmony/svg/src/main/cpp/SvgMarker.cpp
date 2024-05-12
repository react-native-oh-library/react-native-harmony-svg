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
        const auto count = OH_Drawing_CanvasGetSaveCount(canvas);
        saveAndSetupCanvas(canvas, mCTM);
    
        if(markerTransform == nullptr) {
            markerTransform = OH_Drawing_MatrixCreate();
        }else {
            OH_Drawing_MatrixDestroy(markerTransform);
            markerTransform = OH_Drawing_MatrixCreate();
        }
        Point origin = position.origin;
        OH_Drawing_MatrixTranslate(markerTransform, origin.x, origin.y);
        double markerAngle = (mOrient == "auto") ? -1 : std::atof(mOrient.c_str());
        float degrees = 180 + (markerAngle == -1 ? position.angle : static_cast<float>(markerAngle));
    
        OH_Drawing_MatrixPreRotate(markerTransform, degrees, origin.x, origin.y);

        if(mMarkerUnits == "strokeWidth"){
            OH_Drawing_MatrixPreScale(markerTransform, strokeWidth / scale_, strokeWidth / scale_, origin.x, origin.y);
        }
        double width = mMarkerWidth;
        double height = mMarkerHeight;
        Rect eRect(0, 0, width, height);
        if(!mAlign.empty()){
            Rect vbRect(mMinX * scale_, mMinY * scale_, (mMinX + mVbWidth) * scale_, (mMinY + mVbHeight) * scale_);
            OH_Drawing_Matrix* viewBoxMatrix = rhon::ViewBox::getTransform(vbRect, eRect, mAlign, mMeetOrSlice);
            float sx = OH_Drawing_MatrixGetValue(viewBoxMatrix, 0);
            float sy = OH_Drawing_MatrixGetValue(viewBoxMatrix, 4);
            OH_Drawing_MatrixPreScale(markerTransform, sx, sy, origin.x, origin.y);
        }
    
        double x = mRefX * scale_;
        double y = mRefY * scale_;
        OH_Drawing_MatrixPreTranslate(markerTransform, -x, -y);
        OH_Drawing_CanvasConcatMatrix(canvas, markerTransform);
        
        OnDrawTraversed(canvas);
    
        OH_Drawing_CanvasRestoreToCount(canvas, count);
        LOG(INFO) << "[SvgMarker] renderMarker done.";
    }
}