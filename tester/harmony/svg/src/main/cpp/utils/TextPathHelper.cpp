#include "TextPathHelper.h"
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_path.h>
namespace rnoh {
namespace svg {

namespace {
constexpr int MSCALE_X = 0; //!< use with getValues/setValues
constexpr int MSKEW_X = 1;  //!< use with getValues/setValues
constexpr int MTRANS_X = 2; //!< use with getValues/setValues
constexpr int MSKEW_Y = 3;  //!< use with getValues/setValues
constexpr int MSCALE_Y = 4; //!< use with getValues/setValues
constexpr int MTRANS_Y = 5; //!< use with getValues/setValues
constexpr int MPERSP_0 = 6; //!< use with getValues/setValues
constexpr int MPERSP_1 = 7; //!< use with getValues/setValues
constexpr int MPERSP_2 = 8; //!< use with getValues/setValues

constexpr double tau = 2.0 * M_PI;
constexpr double radToDeg = 360.0 / tau;
} // namespace

TextPathHelper::TextPathHelper(const std::shared_ptr<SvgTextPath> &textPath, TextAnchor anchor) {
    if (!textPath) {
        return;
    }
    path_ = textPath->getTextPath(), sharpMidLine_ = textPath->getMidLine() == TextPathMidLine::sharp;
    pathLength_ = OH_Drawing_PathGetLength(path_.get(), false);

    endOfRendering_ = pathLength_;
    side_ = textPath->getSide() == TextPathSide::right ? -1 : 1;
    absoluteStartOffset_ = textPath->getStartOffset();
    isClosed_ = OH_Drawing_PathIsClosed(path_.get(), false);
    if (isClosed_) {
        startOfRendering_ = absoluteStartOffset_ + (anchor == TextAnchor::middle ? -pathLength_ / 2.0 : 0);
        endOfRendering_ = startOfRendering_ + pathLength_;
    }
}

bool TextPathHelper::GetMatrixOnPath(const Params &p, drawing::Matrix &mid) {
    const double endPoint = p.startPoint + p.charWidth;
    const double halfWay = p.charWidth / 2;
    const double midPoint = p.startPoint + halfWay;
    if (midPoint > endOfRendering_) {
        return false;
    } else if (midPoint < startOfRendering_) {
        return false;
    }
    if (sharpMidLine_) {
        OH_Drawing_PathGetMatrix(path_.get(), false, midPoint, mid.get(), GET_POSITION_AND_TANGENT_MATRIX);
    } else {
        drawing::Matrix start;
        drawing::Matrix end;
        if (p.startPoint < 0) {
            OH_Drawing_PathGetMatrix(path_.get(), false, p.startPoint, start.get(), GET_POSITION_AND_TANGENT_MATRIX);
            start.PreTranslate(p.startPoint, 0);
        } else {
            OH_Drawing_PathGetMatrix(path_.get(), false, p.startPoint, start.get(), GET_POSITION_MATRIX);
        }
        OH_Drawing_PathGetMatrix(path_.get(), true, midPoint, mid.get(), GET_POSITION_MATRIX);

        if (endPoint > pathLength_) {
            OH_Drawing_PathGetMatrix(path_.get(), false, pathLength_, end.get(), GET_POSITION_AND_TANGENT_MATRIX);
            end.PreTranslate((endPoint - pathLength_), 0);
        } else {
            OH_Drawing_PathGetMatrix(path_.get(), false, endPoint, end.get(), GET_POSITION_MATRIX);
        }

        double startX = OH_Drawing_MatrixGetValue(start.get(), MTRANS_X);
        double startY = OH_Drawing_MatrixGetValue(start.get(), MTRANS_Y);
        double endX = OH_Drawing_MatrixGetValue(end.get(), MTRANS_X);
        double endY = OH_Drawing_MatrixGetValue(end.get(), MTRANS_Y);

        double lineX = endX - startX;
        double lineY = endY - startY;

        double glyphMidlineAngle = std::atan2(lineY, lineX);
        mid.PreRotate((glyphMidlineAngle * radToDeg * side_), 0, 0);
    }

    mid.PreTranslate(-halfWay, p.dy);
    mid.PreScale(scaleDirection_, side_, 0, 0);
    mid.PostTranslate(0, p.y);
    return true;
}

} // namespace svg
} // namespace rnoh