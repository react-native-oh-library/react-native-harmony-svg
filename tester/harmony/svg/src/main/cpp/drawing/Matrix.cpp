#include "Matrix.h"

namespace rnoh::drawing {

Matrix::Matrix() : matrix_(UniqueNativeMatrix(OH_Drawing_MatrixCreate(), &OH_Drawing_MatrixDestroy)) {}

Matrix::Matrix(Matrix const &other) : Matrix() { *this = other; }

Matrix &Matrix::operator=(Matrix const &other) {
    if (this != &other) {
        auto scaleX = OH_Drawing_MatrixGetValue(other.matrix_.get(), 0);
        auto skewX = OH_Drawing_MatrixGetValue(other.matrix_.get(), 1);
        auto transX = OH_Drawing_MatrixGetValue(other.matrix_.get(), 2);
        auto skewY = OH_Drawing_MatrixGetValue(other.matrix_.get(), 3);
        auto scaleY = OH_Drawing_MatrixGetValue(other.matrix_.get(), 4);
        auto transY = OH_Drawing_MatrixGetValue(other.matrix_.get(), 5);
        auto persp0 = OH_Drawing_MatrixGetValue(other.matrix_.get(), 6);
        auto persp1 = OH_Drawing_MatrixGetValue(other.matrix_.get(), 7);
        auto persp2 = OH_Drawing_MatrixGetValue(other.matrix_.get(), 8);
        OH_Drawing_MatrixSetMatrix(matrix_.get(), scaleX, skewX, transX, skewY, scaleY, transY, persp0, persp1, persp2);
    }
    return *this;
}


Matrix Matrix::CreateRotation(float deg, float x, float y) {
    return Matrix(OH_Drawing_MatrixCreateRotation(deg, x, y));
}
Matrix Matrix::CreateScale(float sx, float sy, float px, float py) {
    return Matrix(OH_Drawing_MatrixCreateScale(sx, sy, px, py));
}
Matrix Matrix::CreateTranslation(float dx, float dy) { return Matrix(OH_Drawing_MatrixCreateTranslation(dx, dy)); }

void Matrix::PreRotate(float degree, float px, float py) { OH_Drawing_MatrixPreRotate(matrix_.get(), degree, px, py); }
void Matrix::PreScale(float sx, float sy, float px, float py) {
    OH_Drawing_MatrixPreScale(matrix_.get(), sx, sy, px, py);
}
void Matrix::PreTranslate(float dx, float dy) { OH_Drawing_MatrixPreTranslate(matrix_.get(), dx, dy); }

void Matrix::PostRotate(float degree, float px, float py) {
    OH_Drawing_MatrixPostRotate(matrix_.get(), degree, px, py);
}
void Matrix::PostScale(float sx, float sy, float px, float py) {
    OH_Drawing_MatrixPostScale(matrix_.get(), sx, sy, px, py);
}
void Matrix::PostTranslate(float dx, float dy) { OH_Drawing_MatrixPostTranslate(matrix_.get(), dx, dy); }

void Matrix::Rotate(float degree, float px, float py) { OH_Drawing_MatrixRotate(matrix_.get(), degree, px, py); }
void Matrix::Translate(float dx, float dy) { OH_Drawing_MatrixTranslate(matrix_.get(), dx, dy); }
void Matrix::Scale(float sx, float sy, float px, float py) { OH_Drawing_MatrixScale(matrix_.get(), sx, sy, px, py); }

Matrix Matrix::Concat(const Matrix &other) const {
    Matrix result;
    OH_Drawing_MatrixConcat(result.matrix_.get(), matrix_.get(), other.matrix_.get());
    return result;
}

std::optional<Matrix> Matrix::Invert() const {
    Matrix result;
    if (OH_Drawing_MatrixInvert(matrix_.get(), result.matrix_.get())) {
        return result;
    }
    return std::nullopt;
}

float Matrix::GetValue(int index) const { return OH_Drawing_MatrixGetValue(matrix_.get(), index); }

void Matrix::SetMatrix(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0,
                       float persp1, float persp2) {
    OH_Drawing_MatrixSetMatrix(matrix_.get(), scaleX, skewX, transX, skewY, scaleY, transY, persp0, persp1, persp2);
}

Matrix::Point drawing::Matrix::MapPoint(const Matrix::Point &point) const {
    Point result;
    OH_Drawing_MatrixMapPoints(matrix_.get(), &point, &result, 1);
    return result;
}

std::vector<Matrix::Point> drawing::Matrix::MapPoints(const std::vector<Matrix::Point> &points) const {
    std::vector<Matrix::Point> result(points.size());
    OH_Drawing_MatrixMapPoints(matrix_.get(), points.data(), result.data(), points.size());
    return result;
}

drawing::Rect drawing::Matrix::MapRect(const drawing::Rect &rect) const {
    Rect result;
    OH_Drawing_MatrixMapRect(matrix_.get(), rect.get(), result.get());
    return result;
}

void Matrix::Reset() { OH_Drawing_MatrixReset(matrix_.get()); }


} // namespace rnoh::drawing