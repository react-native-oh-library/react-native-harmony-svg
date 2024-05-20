//
// Created on 2024/5/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGMARKER_H
#define HARMONY_SVGMARKER_H

#include "SvgQuote.h"
#include "properties/Dimension.h"
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
namespace svg {

class SvgMarker : public SvgQuote {
public:
    SvgMarker() = default;
    ~SvgMarker() override = default;

    void setRefX(Dimension refX) { mRefX = refX.ConvertToPx(); }

    void setRefY(Dimension refY) { mRefY = refY.ConvertToPx(); }

    void setMarkerWidth(Dimension markerWidth) {
        mMarkerWidth = markerWidth.ConvertToPx();
        LOG(INFO) << "[SvgMarker] setMarkerWidth mMarkerWidth=" << mMarkerWidth;
    }

    void setMarkerHeight(Dimension markerHeight) {
        mMarkerHeight = markerHeight.ConvertToPx();
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
    void saveAndSetupCanvas(OH_Drawing_Canvas *canvas, drawing::Matrix ctm) {
        OH_Drawing_CanvasSave(canvas);
        mCTM = mMatrix.Concat(mTransform);
        OH_Drawing_CanvasConcatMatrix(canvas, mCTM.get());
        mCTM = mCTM.Concat(ctm);
        mInvCTM = mCTM.Invert();
    }

private:
    drawing::Matrix markerTransform;
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
    
    drawing::Matrix mCTM;
    drawing::Matrix mMatrix;
    drawing::Matrix mTransform;
    std::optional<drawing::Matrix> mInvCTM;
};

} // namespace svg
} // namespace rnoh

#endif // HARMONY_SVGMARKER_H
