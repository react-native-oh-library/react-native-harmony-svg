//
// Created on 2024/5/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SvgMarkerPosition_H
#define HARMONY_SvgMarkerPosition_H

#include <cmath>

namespace rnoh {
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
    Point* points;
    int numPoints;

public:
    PathElement(ElementType _type, Point* _points, int _numPoints)
        : type(_type), points(_points), numPoints(_numPoints) {}
};

class SvgMarkerPosition {
private:
    static std::vector<SvgMarkerPosition> positions_;
    static int element_index_;
    static Point origin_;
    static Point subpath_start_;
    static Point in_slope_;
    static Point out_slope_;

    static bool auto_start_reverse_; // TODO

public:
    static RNSVGMarkerType type;
    static Point origin;
    static double angle;
    
    SvgMarkerPosition(RNSVGMarkerType t, Point o, double a){
        type = t;
        origin = o;
        angle = a;
    }

    static std::vector<SvgMarkerPosition> fromPath(const std::vector<PathElement>& elements) {
        positions_ = {};
        // 其他变量的初始化
        element_index_ = 0;
        origin_ = {0, 0};
        subpath_start_ = {0, 0};
        for (const PathElement& e : elements) {
            UpdateFromPathElement(e);
        }

        PathIsDone();
        return positions_;
    }

private:
    static void PathIsDone() {
        double angle = CurrentAngle(RNSVGMarkerType::kEndMarker); // 获取当前角度
        positions_.push_back(SvgMarkerPosition(RNSVGMarkerType::kEndMarker, origin_, angle));
    }

    static double rad2deg(double rad) {
        const double RNSVG_radToDeg = 180.0 / M_PI; // 弧度转换为度的比例关系
        return rad * RNSVG_radToDeg;
    }

    static double SlopeAngleRadians(Point p) {
        return std::atan2(p.y, p.x);
    }

    static double BisectingAngle(double in_angle, double out_angle) {
        if (std::abs(in_angle - out_angle) > 180) in_angle += 360;
        return (in_angle + out_angle) / 2.0;
    }

    static double CurrentAngle(RNSVGMarkerType type) {
        // 根据不同的 Marker 类型计算当前角度
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

    static Point subtract(Point p1, Point p2) {
        return {p2.x - p1.x, p2.y - p1.y};
    }

    static bool isZero(Point p) {
        return p.x == 0 && p.y == 0;
    }

    static void ComputeQuadTangents(SegmentData& data, Point start, Point control, Point end) {
        data.start_tangent = subtract(control, start);
        data.end_tangent = subtract(end, control);
        if (isZero(data.start_tangent)) data.start_tangent = data.end_tangent;
        else if (isZero(data.end_tangent)) data.end_tangent = data.start_tangent;
    }

    static SegmentData ExtractPathElementFeatures(PathElement element) {
        SegmentData data = {{0,0}, {0,0}, {0,0}};
        Point* points = &element.points[0];
        switch (element.type) {
            case ElementType::kCGPathElementAddCurveToPoint:
                data.position = points[2];
                data.start_tangent = subtract(points[0], origin);
                data.end_tangent = subtract(points[2], points[1]);
                if (isZero(data.start_tangent)) ComputeQuadTangents(data, points[0], points[1], points[2]);
                else if (isZero(data.end_tangent)) ComputeQuadTangents(data, origin, points[0], points[1]);
                break;
            case ElementType::kCGPathElementAddQuadCurveToPoint:
                data.position = points[1];
                ComputeQuadTangents(data, origin, points[0], points[1]);
                break;
            case ElementType::kCGPathElementMoveToPoint:
            case ElementType::kCGPathElementAddLineToPoint:
                data.position = points[0];
                data.start_tangent = subtract(data.position, origin);
                data.end_tangent = subtract(data.position, origin);
                break;
            case ElementType::kCGPathElementCloseSubpath:
                data.position = subpath_start_;
                data.start_tangent = subtract(data.position, origin);
                data.end_tangent = subtract(data.position, origin);
                break;
        }
        return data;
    }

    static void UpdateFromPathElement(PathElement element) {
        SegmentData segment_data = ExtractPathElementFeatures(element);
        out_slope_ = segment_data.start_tangent;
        if (element_index_ > 0) {
            RNSVGMarkerType marker_type = element_index_ == 1 ? RNSVGMarkerType::kStartMarker : RNSVGMarkerType::kMidMarker;
            double angle = CurrentAngle(marker_type);
            positions_.push_back({marker_type, origin, angle});
        }
        in_slope_ = segment_data.end_tangent;
        origin = segment_data.position;
        if (element.type == ElementType::kCGPathElementMoveToPoint){
            subpath_start_ = element.points[0];
        }else if (element.type == ElementType::kCGPathElementCloseSubpath) {
            subpath_start_ = {0, 0};
        }
        ++element_index_;
    }
};

RNSVGMarkerType SvgMarkerPosition::type;
Point SvgMarkerPosition::origin(0.0, 0.0);
double SvgMarkerPosition::angle;

}
#endif //HARMONY_SvgMarkerPosition_H
