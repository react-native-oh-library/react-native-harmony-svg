#pragma once

#include <memory>
#include <native_drawing/drawing_brush.h>
#include "ShaderEffect.h"

namespace rnoh::drawing {

class Brush final {

    using UniqueNativeBrush = std::unique_ptr<OH_Drawing_Brush, decltype(&OH_Drawing_BrushDestroy)>;

public:
    Brush();

    Brush(Brush const &);
    Brush &operator=(Brush const &);

    Brush(Brush &&) = default;
    Brush &operator=(Brush &&) = default;

    ~Brush() noexcept = default;

    void SetAntiAlias(bool antiAlias);
    void SetColor(uint32_t color);
    void SetAlpha(uint8_t alpha);

    void SetLinearShaderEffect(
        const OH_Drawing_Point2D* startPt, const OH_Drawing_Point2D* endPt, const uint32_t* colors, const float* pos,
        uint32_t size, OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat);
    void SetRadialShaderEffect(
        const OH_Drawing_Point2D* startPt, float startRadius, const OH_Drawing_Point2D* endPt, float endRadius,
        const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat);

    void Reset();

    OH_Drawing_Brush *get() const { return brush_.get(); }

private:
    UniqueNativeBrush brush_;
    ShaderEffect brushShaderEffect_;
};

} // namespace rnoh::drawing