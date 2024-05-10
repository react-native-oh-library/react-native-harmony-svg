//
// Created on 2024/5/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGMARKER_H
#define HARMONY_SVGMARKER_H

#include "SvgQuote.h"
#include "properties/Dimension.h"
#include "properties/Size.h"
#include "utils/SvgMarkerPositionUtils.h"
#include "Props.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <native_drawing/drawing_register_font.h>
#include <native_drawing/drawing_text_typography.h>
#include <native_drawing/drawing_matrix.h>

namespace rnoh {

class SvgMarker : public SvgQuote {
public:
    SvgMarker() = default;
    ~SvgMarker() override = default;

    Size size;

    void setRefX(Dimension refX) { mRefX = ConvertDimensionToPx(refX, size, SvgLengthType::HORIZONTAL); }

    void setRefY(Dimension refY) { mRefY = ConvertDimensionToPx(refY, size, SvgLengthType::VERTICAL); }

    void setMarkerWidth(Dimension markerWidth) {
        mMarkerWidth = ConvertDimensionToPx(markerWidth, size, SvgLengthType::HORIZONTAL);
        LOG(INFO) << "[SvgMarker] setMarkerWidth mMarkerWidth=" << mMarkerWidth;
    }

    void setMarkerHeight(Dimension markerHeight) {
        mMarkerHeight = ConvertDimensionToPx(markerHeight, size, SvgLengthType::VERTICAL);
    }

    void setMarkerUnits(std::string markerUnits) { mMarkerUnits = markerUnits; }

    void setOrient(std::string orient) { mOrient = orient; }

    void setMinX(float minX) { mMinX = minX; }

    void setMinY(float minY) { mMinY = minY; }

    void setVbWidth(float vbWidth) { mVbWidth = vbWidth; }

    void setVbHeight(float vbHeight) { mVbHeight = vbHeight; }

    void setAlign(std::string align) { mAlign = align; }

    void setMeetOrSlice(int meetOrSlice) { mMeetOrSlice = meetOrSlice; }

    void renderMarker(OH_Drawing_Canvas *canvas, const SvgMarkerPosition &position, float strokeWidth);

    // todo VirtualView.saveDefinition and Override
    void saveDefinition() {
        //         if (mName != null) {
        //           SvgView svg = getSvgView();
        //           svg.defineMarker(this, mName);
        //           for (int i = 0; i < getChildCount(); i++) {
        //             View node = getChildAt(i);
        //             if (node instanceof VirtualView) {
        //               ((VirtualView) node).saveDefinition();
        //             }
        //           }
        //         }
    }

    // todo VirtualView.relativeOnWidth
    double relativeOnWidth(double markerWidth) { return markerWidth; }

    // todo VirtualView.relativeOnHeight
    double relativeOnHeight(double markerHeight) { return markerHeight; }

    /**
     * from VirtualView.saveAndSetupCanvas
     *
     * Sets up the transform matrix on the canvas before an element is drawn.
     *
     * <p>NB: for perf reasons this does not apply opacity, as that would mean creating a new canvas
     * layer (which allocates an offscreen bitmap) and having it composited afterwards. Instead, the
     * drawing code should apply opacity recursively.
     *
     * @param canvas the canvas to set up
     * @param ctm current transformation matrix
     */
    void saveAndSetupCanvas(OH_Drawing_Canvas *canvas, OH_Drawing_Matrix *ctm) {
        OH_Drawing_CanvasSave(canvas);
        OH_Drawing_MatrixConcat(mCTM, mMatrix, mTransform);
        OH_Drawing_CanvasConcatMatrix(canvas, mCTM);
        OH_Drawing_MatrixConcat(mCTM, mCTM, ctm);
        mCTMInvertible = OH_Drawing_MatrixInvert(mCTM, mInvCTM);
    }

private:
    OH_Drawing_Matrix *markerTransform;
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
    int mScale = 2;

    // todo 父类 VirtualView 属性，暂时定义
    OH_Drawing_Matrix *mCTM;
    OH_Drawing_Matrix *mMatrix;
    OH_Drawing_Matrix *mTransform;
    OH_Drawing_Matrix *mInvCTM;
    bool mCTMInvertible;
};
} // namespace rnoh

#endif // HARMONY_SVGMARKER_H
