#include <native_drawing/drawing_matrix.h>
#include <memory>
namespace rnoh::drawing {
class Matrix {
public:
    Matrix() : mat_(MatUPtr(OH_Drawing_MatrixCreate(), OH_Drawing_MatrixDestroy)) {}
    OH_Drawing_Matrix *operator&() { return mat_.get(); }

private:
    using MatUPtr = std::unique_ptr<OH_Drawing_Matrix, decltype(&OH_Drawing_MatrixDestroy)>;
    MatUPtr mat_;
};
} // namespace rnoh::drawing