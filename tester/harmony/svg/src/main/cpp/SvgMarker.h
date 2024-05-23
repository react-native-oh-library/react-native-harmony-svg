//
// Created on 2024/5/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGMARKER_H
#define HARMONY_SVGMARKER_H

#include "SvgQuote.h"
#include "properties/Dimension.h"
#include "utils/SvgAttributesParser.h"
#include "utils/SvgMarkerPositionUtils.h"
#include <sstream>
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

    void setRefX(const std::string &refX) {
        markerAttribute_.refX = SvgAttributesParser::ParseDimension(refX, true);
    }

    void setRefY(const std::string &refY) {
        markerAttribute_.refY = SvgAttributesParser::ParseDimension(refY, true);
    }

    void setMarkerWidth(const std::string &markerWidth) {
        markerAttribute_.markerWidth = SvgAttributesParser::ParseDimension(markerWidth, true);
    }

    void setMarkerHeight(const std::string &markerHeight) {
        markerAttribute_.markerHeight = SvgAttributesParser::ParseDimension(markerHeight, true);
    }

    void setMarkerUnits(const std::string &markerUnits) {
        markerAttribute_.markerUnits = markerUnits;
    }

    void setOrient(const std::string &orient) {
        markerAttribute_.orient = orient;
    }

    void setMinX(double minX) { markerAttribute_.minX = Dimension(minX, DimensionUnit::VP); }

    void setMinY(double minY) { markerAttribute_.minY = Dimension(minY, DimensionUnit::VP); }

    void setVbWidth(double vbWidth) { markerAttribute_.vbWidth = Dimension(vbWidth, DimensionUnit::VP); }

    void setVbHeight(double vbHeight) { markerAttribute_.vbHeight = Dimension(vbHeight, DimensionUnit::VP); }

    void setAlign(std::string align) { markerAttribute_.align = align; }

    void setMeetOrSlice(int meetOrSlice) { markerAttribute_.meetOrSlice = meetOrSlice; }

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
        cTM_ = mMatrix.Concat(mTransform);
        OH_Drawing_CanvasConcatMatrix(canvas, cTM_.get());
        cTM_ = cTM_.Concat(ctm);
        mInvCTM = cTM_.Invert();
    }

private:
    SvgMarkerAttribute markerAttribute_;
    drawing::Matrix markerTransform;
    drawing::Matrix mMatrix;
    drawing::Matrix mTransform;
    std::optional<drawing::Matrix> mInvCTM;
};

} // namespace svg
} // namespace rnoh

#endif // HARMONY_SVGMARKER_H
