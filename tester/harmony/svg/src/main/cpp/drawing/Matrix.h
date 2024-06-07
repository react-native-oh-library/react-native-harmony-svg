#pragma once

#include "Rect.h"
#include <memory>
#include <optional>
#include <vector>
#include <native_drawing/drawing_matrix.h>

namespace rnoh::drawing {

class Matrix final {
    using UniqueNativeMatrix = std::unique_ptr<OH_Drawing_Matrix, decltype(&OH_Drawing_MatrixDestroy)>;
    using Point = OH_Drawing_Point2D;

public:
    Matrix();

    Matrix(Matrix const &);
    Matrix &operator=(Matrix const &);

    Matrix(Matrix &&) = default;
    Matrix &operator=(Matrix &&) = default;

    ~Matrix() noexcept = default;

    static Matrix CreateRotation(float deg, float x, float y);
    static Matrix CreateScale(float sx, float sy, float px, float py);
    static Matrix CreateTranslation(float dx, float dy);
    void PreRotate(float degree, float px, float py);
    void PreScale(float sx, float sy, float px, float py);
    void PreTranslate(float dx, float dy);
    void PostRotate(float degree, float px, float py);
    void PostScale(float sx, float sy, float px, float py);
    void PostTranslate(float dx, float dy);
    void Rotate(float degree, float px, float py);
    void Translate(float dx, float dy);
    void Scale(float sx, float sy, float px, float py);

    Matrix Concat(const Matrix &other) const;
    std::optional<Matrix> Invert() const;

    float GetValue(int index) const;

    void SetMatrix(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0,
                   float persp1, float persp2);

    Point MapPoint(const Point &point) const;
    std::vector<Point> MapPoints(const std::vector<Point> &points) const;

    drawing::Rect MapRect(const drawing::Rect &rect) const;

    void Reset();

    OH_Drawing_Matrix *get() const { return matrix_.get(); }

private:
    Matrix(OH_Drawing_Matrix *rawMatrix) : matrix_(UniqueNativeMatrix(rawMatrix, &OH_Drawing_MatrixDestroy)) {}

    UniqueNativeMatrix matrix_;
};

} // namespace rnoh::drawing