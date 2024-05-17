#pragma once
#include "drawing/Matrix.h"
#include <native_drawing/drawing_path.h>
#include "SvgTextPath.h"
namespace rnoh {
namespace svg {

class TextPathHelper {
    public:
    TextPathHelper(const std::shared_ptr<svg::SvgTextPath>& textPath, svg::TextAnchor anchor);

    double GetStartOffset() const {
        return absoluteStartOffset_;
    }

    int GetSide() const {
        return side_;
    }

    bool Valid() const {
        return pathLength_ > 0.0;
    }

    void SetScaleSpacingAndGlyphs(double value) {
        scaleDirection_ = value * side_;
    }

    struct Params {
        double charWidth = 0.0;
        double startPoint = 0.0;
        double y = 0.0;
        double dy = 0.0;
    };
    /**
     * @brief Set transform matrix to paint the character at the given position on the path.
     *
     * @return true if this character can be skipped
     */
    bool GetMatrixOnPath(const Params& p, drawing::Matrix &mat);

private:
    drawing::Path path_ = drawing::Path();
    int side_ = 0;
    double pathLength_ = 0.0;
    double startOfRendering_ = 0.0;
    double endOfRendering_ = 0.0;
    double absoluteStartOffset_ = 0.0;
    double scaleDirection_ = 1.0;
    bool sharpMidLine_ = false;
    bool isClosed_ = false;
};

} // namespace svg
} // namespace rnoh