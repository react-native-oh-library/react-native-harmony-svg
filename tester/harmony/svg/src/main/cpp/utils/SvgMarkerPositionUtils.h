//
// Created on 2024/5/9.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGMARKERPOSITIONUTIL_H
#define HARMONY_SVGMARKERPOSITIONUTIL_H

#include <cmath>
#include <vector>

namespace rnoh {
namespace svg {

enum class RNSVGMarkerType {
  kStartMarker,
  kMidMarker,
  kEndMarker
};

enum class ElementType {
  kCGPathElementAddCurveToPoint,
  kCGPathElementAddQuadCurveToPoint,
  kCGPathElementMoveToPoint,
  kCGPathElementAddLineToPoint,
  kCGPathElementCloseSubpath
};

class Point {
public:
    double x;
    double y;

public:
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}
};

class SegmentData {
public:
    Point start_tangent;
    Point end_tangent;
    Point position; 

    SegmentData(const Point& _start_tangent, const Point& _end_tangent, const Point& _position)
        : start_tangent(_start_tangent), end_tangent(_end_tangent), position(_position) {}
};

class PathElement {
public:
    ElementType type;
    std::vector<Point> points;

public:
    PathElement(ElementType _type, std::vector<Point> _points)
        : type(_type), points(_points) {}
};

class SvgMarkerPosition {
public:
    RNSVGMarkerType type;
    Point origin = {0.0, 0.0};
    double angle;
    
    SvgMarkerPosition(RNSVGMarkerType _type, Point _origin, double _angle): type(_type), origin(_origin), angle(_angle) {}
};

namespace SvgMarkerPositionUtils{
    static std::vector<SvgMarkerPosition> positions_;
    static int element_index_;
    static Point origin_ = {0, 0};
    static Point subpath_start_ = {0, 0};
    static Point in_slope_ = {0, 0};
    static Point out_slope_ = {0, 0};

    static bool auto_start_reverse_; // TODO

    //ios only, use in renderMarker.
    inline double deg2rad(double deg) {
        const double RNSVG_degToRad = M_PI / 180.0;
        return deg * RNSVG_degToRad;
    }

    inline double rad2deg(double rad) {
        const double RNSVG_radToDeg = 180.0 / M_PI;
        return rad * RNSVG_radToDeg;
    }

    inline double SlopeAngleRadians(Point p) {
        return std::atan2(p.y, p.x);
    }

    inline double BisectingAngle(double in_angle, double out_angle) {
        if (std::abs(in_angle - out_angle) > 180) in_angle += 360;
        return (in_angle + out_angle) / 2.0;
    }

    inline Point subtract(Point p1, Point p2) {
        return {p2.x - p1.x, p2.y - p1.y};
    }

    inline bool isZero(Point p) {
        return p.x == 0 && p.y == 0;
    }

    inline double CurrentAngle(RNSVGMarkerType type) {
        double in_angle = rad2deg(SlopeAngleRadians(in_slope_));
        double out_angle = rad2deg(SlopeAngleRadians(out_slope_));
        switch (type) {
            case RNSVGMarkerType::kStartMarker:
                if (auto_start_reverse_) out_angle += 180;
                return out_angle;
            case RNSVGMarkerType::kMidMarker:
                return BisectingAngle(in_angle, out_angle);
            case RNSVGMarkerType::kEndMarker:
                return in_angle;
        }
        return 0;
    }

    inline void ComputeQuadTangents(SegmentData& data, Point start, Point control, Point end) {
        data.start_tangent = subtract(control, start);
        data.end_tangent = subtract(end, control);
        if (isZero(data.start_tangent)) data.start_tangent = data.end_tangent;
        else if (isZero(data.end_tangent)) data.end_tangent = data.start_tangent;
    }

    inline SegmentData ExtractPathElementFeatures(PathElement element) {
        SegmentData data = {{0,0}, {0,0}, {0,0}};
        std::vector<Point> points = element.points;
        switch (element.type) {
            case ElementType::kCGPathElementAddCurveToPoint:
                data.position = points[2];
                data.start_tangent = subtract(points[0], origin_);
                data.end_tangent = subtract(points[2], points[1]);
                if (isZero(data.start_tangent)) ComputeQuadTangents(data, points[0], points[1], points[2]);
                else if (isZero(data.end_tangent)) ComputeQuadTangents(data, origin_, points[0], points[1]);
                break;
            case ElementType::kCGPathElementAddQuadCurveToPoint:
                data.position = points[1];
                ComputeQuadTangents(data, origin_, points[0], points[1]);
                break;
            case ElementType::kCGPathElementMoveToPoint:
            case ElementType::kCGPathElementAddLineToPoint:
                data.position = points[0];
                data.start_tangent = subtract(data.position, origin_);
                data.end_tangent = subtract(data.position, origin_);
                break;
            case ElementType::kCGPathElementCloseSubpath:
                data.position = subpath_start_;
                data.start_tangent = subtract(data.position, origin_);
                data.end_tangent = subtract(data.position, origin_);
                break;
        }
        return data;
    }

    inline void UpdateFromPathElement(PathElement element) {
        SegmentData segment_data = ExtractPathElementFeatures(element);
        out_slope_ = segment_data.start_tangent;
        if (element_index_ > 0) {
            RNSVGMarkerType marker_type = element_index_ == 1 ? RNSVGMarkerType::kStartMarker : RNSVGMarkerType::kMidMarker;
            double angle = CurrentAngle(marker_type);
            positions_.push_back({marker_type, origin_, angle});
        }
        in_slope_ = segment_data.end_tangent;
        origin_ = segment_data.position;
        if (element.type == ElementType::kCGPathElementMoveToPoint){
            subpath_start_ = element.points[0];
        }else if (element.type == ElementType::kCGPathElementCloseSubpath) {
            subpath_start_ = {0, 0};
        }
        ++element_index_;
    }

    inline void PathIsDone() {
        double angle = CurrentAngle(RNSVGMarkerType::kEndMarker);
        positions_.push_back(SvgMarkerPosition(RNSVGMarkerType::kEndMarker, origin_, angle));
    }

    inline std::vector<SvgMarkerPosition> fromPath(const std::vector<PathElement>& elements) {
        positions_.clear();
        element_index_ = 0;
        origin_ = {0, 0};
        subpath_start_ = {0, 0};
        for (const PathElement& e : elements) {
            UpdateFromPathElement(e);
        }
        PathIsDone();
        return positions_;
    }
}

} // namespace svg
} // namespace rnoh

#endif //HARMONY_SVGMARKERPOSITIONUTIL_H
