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
    pathLength_ = path_.GetLength(false);

    endOfRendering_ = pathLength_;
    side_ = textPath->getSide() == TextPathSide::right ? -1 : 1;
    absoluteStartOffset_ = textPath->getStartOffset();
    isClosed_ = path_.IsClosed(false); 
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
        mid = path_.GetMatrix(false, midPoint, GET_POSITION_AND_TANGENT_MATRIX).value_or(drawing::Matrix());
    } else {
        drawing::Matrix start;
        drawing::Matrix end;
        if (p.startPoint < 0) {
            start = path_.GetMatrix(false, p.startPoint, GET_POSITION_AND_TANGENT_MATRIX).value_or(drawing::Matrix());
            start.PreTranslate(p.startPoint, 0);
        } else {
            start = path_.GetMatrix(false, p.startPoint, GET_POSITION_MATRIX).value_or(drawing::Matrix());
        }
        mid = path_.GetMatrix(true, midPoint, GET_POSITION_MATRIX).value_or(drawing::Matrix());

        if (endPoint > pathLength_) {
            end = path_.GetMatrix(false, pathLength_, GET_POSITION_AND_TANGENT_MATRIX).value_or(drawing::Matrix());
            end.PreTranslate((endPoint - pathLength_), 0);
        } else {
            end = path_.GetMatrix(false, pathLength_, GET_POSITION_MATRIX).value_or(drawing::Matrix());
        }

        double startX = start.GetValue(MTRANS_X);
        double startY = start.GetValue(MTRANS_Y);

        double endX = end.GetValue(MTRANS_X); 
        double endY = end.GetValue(MTRANS_Y); 

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