#pragma once

#include <memory>
#include <native_drawing/drawing_path.h>
#include "Matrix.h"
#include "Rect.h"
#include "RoundRect.h"

namespace rnoh::drawing {

class Path final {
    using UniqueNativePath = std::unique_ptr<OH_Drawing_Path, decltype(&OH_Drawing_PathDestroy)>;

public:
    using Direction = OH_Drawing_PathDirection;
    using AddMode = OH_Drawing_PathAddMode;
    using FillType = OH_Drawing_PathFillType;
    using MeasureMatrixFlags = OH_Drawing_PathMeasureMatrixFlags;
    using OpMode = OH_Drawing_PathOpMode;

    Path();

    Path(Path const &);
    Path &operator=(Path const &);

    Path(Path &&) = default;
    Path &operator=(Path &&) = default;

    ~Path() noexcept = default;

    void Reset();

    void MoveTo(float x, float y);

    void LineTo(float x, float y);

    void ArcTo(float x1, float y1, float x2, float y2, float startDeg, float sweepDeg);

    void QuadTo(float ctrlX, float ctrlY, float endX, float endY);

    void ConicTo(float ctrlX, float ctrlY, float endX, float endY, float weight);

    void CubicTo(float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2, float endX, float endY);

    void RMoveTo(float x, float y);

    void RLineTo(float x, float y);

    void RQuadTo(float ctrlX, float ctrlY, float endX, float endY);

    void RConicTo(float ctrlX, float ctrlY, float endX, float endY, float weight);

    void RCubicTo(float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2, float endX, float endY);

    void AddRect(float left, float top, float right, float bottom, Direction);
    void AddRectWithInitialCorner(const Rect &, Direction, uint32_t start);
    void AddRoundRect(const RoundRect &roundRect, Direction);

    void AddOvalWithInitialPoint(const Rect &, uint32_t start, Direction);
    void AddOval(const Rect &, Direction);

    void AddArc(const Rect &, float startAngle, float sweepAngle);

    void AddPath(const Path &src);
    void AddPath(const Path &src, const Matrix &);

    void AddPathWithMatrixAndMode(const Path &src, const Matrix &, AddMode);
    void AddPathWithMode(const Path &src, AddMode);

    void AddPathWithOffsetAndMode(const Path &src, float dx, float dy, AddMode);
    void AddPolygon(const OH_Drawing_Point2D *points, uint32_t count, bool isClosed);

    void AddCircle(float x, float y, float radius, Direction);

    static std::optional<Path> BuildFromSvgString(const char *str);

    bool Contains(float x, float y);


    void Transform(const Matrix &);


    Path TransformWithPerspectiveClip(const Matrix &, bool applyPerspectiveClip);


    void SetFillType(FillType);

    float GetLength(bool forceClosed);

    Rect GetBounds();

    void Close();

    Path Offset(float dx, float dy);

    bool IsClosed(bool forceClosed);

    bool GetPositionTangent(bool forceClosed, float distance, OH_Drawing_Point2D *position,
                            OH_Drawing_Point2D *tangent);

    bool Op(Path &source, OpMode mode);
    
    bool Difference(Path &source);

    bool Intersect(Path &source);

    bool Union(Path &source);

    bool Xor(Path &source);

    bool ReverseDifference(Path &source);

    std::optional<Matrix> GetMatrix(bool forceClosed, float distance, MeasureMatrixFlags flag);

    OH_Drawing_Path *get() const { return path_.get(); }

private:
    UniqueNativePath path_;
};

} // namespace rnoh::drawing