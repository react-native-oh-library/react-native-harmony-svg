#pragma once

#include <memory>
#include <optional>
#include <native_drawing/drawing_matrix.h>

namespace rnoh::drawing {

class Matrix final {
    using UniqueNativeMatrix = std::unique_ptr<OH_Drawing_Matrix, decltype(&OH_Drawing_MatrixDestroy)>;

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

    void Reset();

    OH_Drawing_Matrix *get() const {
        return matrix_.get(); }

private:
    Matrix(OH_Drawing_Matrix *rawMatrix) : matrix_(UniqueNativeMatrix(rawMatrix, &OH_Drawing_MatrixDestroy)) {}

    UniqueNativeMatrix matrix_;
};

} // namespace rnoh::drawing