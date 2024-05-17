#include "Path.h"
#include <native_drawing/drawing_rect.h>

namespace rnoh {
namespace drawing {

Path::Path() : path_(UniqueNativePath(OH_Drawing_PathCreate(), &OH_Drawing_PathDestroy)) {}

Path::Path(Path const &other)
    : path_(UniqueNativePath(OH_Drawing_PathCopy(other.path_.get()), &OH_Drawing_PathDestroy)) {}

Path &Path::operator=(Path const &other) {
    if (this != &other) {
        path_ = UniqueNativePath(OH_Drawing_PathCopy(other.path_.get()), &OH_Drawing_PathDestroy);
    }
    return *this;
}

void Path::Reset() { OH_Drawing_PathReset(path_.get()); }

void Path::MoveTo(float x, float y) { OH_Drawing_PathMoveTo(get(), x, y); }

void Path::LineTo(float x, float y) { OH_Drawing_PathLineTo(get(), x, y); }

void Path::ArcTo(float x1, float y1, float x2, float y2, float startDeg, float sweepDeg) {
    OH_Drawing_PathArcTo(get(), x1, y1, x2, y2, startDeg, sweepDeg);
}

void Path::QuadTo(float ctrlX, float ctrlY, float endX, float endY) {
    OH_Drawing_PathQuadTo(get(), ctrlX, ctrlY, endX, endY);
}

void Path::ConicTo(float ctrlX, float ctrlY, float endX, float endY, float weight) {
    OH_Drawing_PathConicTo(get(), ctrlX, ctrlY, endX, endY, weight);
}

void Path::CubicTo(float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2, float endX, float endY) {
    OH_Drawing_PathCubicTo(get(), ctrlX1, ctrlY1, ctrlX2, ctrlY2, endX, endY);
}

void Path::RMoveTo(float x, float y) { OH_Drawing_PathRMoveTo(get(), x, y); }

void Path::RLineTo(float x, float y) { OH_Drawing_PathRLineTo(get(), x, y); }

void Path::RQuadTo(float ctrlX, float ctrlY, float endX, float endY) {
    OH_Drawing_PathRQuadTo(get(), ctrlX, ctrlY, endX, endY);
}

void Path::RConicTo(float ctrlX, float ctrlY, float endX, float endY, float weight) {
    OH_Drawing_PathRConicTo(get(), ctrlX, ctrlY, endX, endY, weight);
}

void Path::RCubicTo(float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2, float endX, float endY) {
    OH_Drawing_PathRCubicTo(get(), ctrlX1, ctrlY1, ctrlX2, ctrlY2, endX, endY);
}

void Path::AddRect(float left, float top, float right, float bottom, Direction direction) {
    OH_Drawing_PathAddRect(get(), left, top, right, bottom, direction);
}

void Path::AddRectWithInitialCorner(const Rect &rect, Direction direction, uint32_t start) {
    OH_Drawing_PathAddRectWithInitialCorner(get(), rect.get(), direction, start);
}

void Path::AddRoundRect(const RoundRect &roundRect, Direction direction) {
    OH_Drawing_PathAddRoundRect(get(), roundRect.get(), direction);
}

void Path::AddOvalWithInitialPoint(const Rect &rect, uint32_t start, Direction direction) {
    OH_Drawing_PathAddOvalWithInitialPoint(get(), rect.get(), start, direction);
}

void Path::AddOval(const Rect &rect, Direction direction) { OH_Drawing_PathAddOval(get(), rect.get(), direction); }

void Path::AddArc(const Rect &rect, float startAngle, float sweepAngle) {
    OH_Drawing_PathAddArc(get(), rect.get(), startAngle, sweepAngle);
}

void Path::AddPath(const Path &src) {
    OH_Drawing_PathAddPath(get(), src.get(), nullptr);
}

void Path::AddPath(const Path &src, const Matrix &matrix) { OH_Drawing_PathAddPath(get(), src.get(), matrix.get()); }

void Path::AddPathWithMatrixAndMode(const Path &src, const Matrix &matrix, AddMode mode) {
    OH_Drawing_PathAddPathWithMatrixAndMode(get(), src.get(), matrix.get(), mode);
}

void Path::AddPathWithMode(const Path &src, AddMode mode) { OH_Drawing_PathAddPathWithMode(get(), src.get(), mode); }

void Path::AddPathWithOffsetAndMode(const Path &src, float dx, float dy, AddMode mode) {
    OH_Drawing_PathAddPathWithOffsetAndMode(get(), src.get(), dx, dy, mode);
}

void Path::AddPolygon(const OH_Drawing_Point2D *points, uint32_t count, bool isClosed) {
    OH_Drawing_PathAddPolygon(get(), points, count, isClosed);
}

void Path::AddCircle(float x, float y, float radius, Direction direction) {
    OH_Drawing_PathAddCircle(get(), x, y, radius, direction);
}

std::optional<Path> Path::BuildFromSvgString(const char *str) { 
    Path path;
    if (OH_Drawing_PathBuildFromSvgString(path.get(), str)) {
        return path;
    } else {
        return std::nullopt;
    }
 }

bool Path::Contains(float x, float y) { return OH_Drawing_PathContains(get(), x, y); }

void Path::Transform(const Matrix &matrix) { OH_Drawing_PathTransform(get(), matrix.get()); }

Path Path::TransformWithPerspectiveClip(const Matrix &matrix, bool applyPerspectiveClip) {
    Path path;
    OH_Drawing_PathTransformWithPerspectiveClip(get(), matrix.get(), path.get(), applyPerspectiveClip);
    return path;
}

void Path::SetFillType(FillType fillType) { OH_Drawing_PathSetFillType(get(), fillType); }

float Path::GetLength(bool forceClosed) { return OH_Drawing_PathGetLength(get(), forceClosed); }

Rect Path::GetBounds() {
    Rect bounds;
    OH_Drawing_PathGetBounds(get(), bounds.get());
    return bounds;
}

void Path::Close() { OH_Drawing_PathClose(get()); }

Path Path::Offset(float dx, float dy) {
    Path path;
    OH_Drawing_PathOffset(get(), path.get(), dx, dy);
    return path;
}

bool Path::IsClosed(bool forceClosed) { return OH_Drawing_PathIsClosed(get(), forceClosed); }

bool Path::GetPositionTangent(bool forceClosed, float distance, OH_Drawing_Point2D *position,
                              OH_Drawing_Point2D *tangent) {
    return OH_Drawing_PathGetPositionTangent(get(), forceClosed, distance, position, tangent);
}

bool Path::Op(Path &source, OpMode mode) { return OH_Drawing_PathOp(get(), source.get(), mode); }

bool Path::Difference(Path &source) { return Op(source, PATH_OP_MODE_DIFFERENCE); }

bool Path::Intersect(Path &source) { return Op(source, PATH_OP_MODE_INTERSECT); }

bool Path::Union(Path &source) { return Op(source, PATH_OP_MODE_UNION); }

bool Path::Xor(Path &source) { return Op(source, PATH_OP_MODE_XOR); }

bool Path::ReverseDifference(Path &source) {
    return Op(source, PATH_OP_MODE_REVERSE_DIFFERENCE);
}

std::optional<Matrix> Path::GetMatrix(bool forceClosed, float distance, MeasureMatrixFlags flag) {
    Matrix matrix;
    if (OH_Drawing_PathGetMatrix(get(), forceClosed, distance, matrix.get(), flag)) {
        return matrix;
    } else {
        return std::nullopt;
    }
}

} // namespace drawing
} // namespace rnoh