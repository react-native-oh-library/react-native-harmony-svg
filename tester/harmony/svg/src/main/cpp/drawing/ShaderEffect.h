#pragma once

#include <memory>
#include <native_drawing/drawing_shader_effect.h>
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_types.h>

namespace rnoh::drawing {

class ShaderEffect final {

    using UniqueNativeShaderEffect = std::unique_ptr<OH_Drawing_ShaderEffect, decltype(&OH_Drawing_ShaderEffectDestroy)>;

public:
    ShaderEffect();

    void ShaderEffectCreateLinearGradient(
        const OH_Drawing_Point2D* startPt, const OH_Drawing_Point2D* endPt, const uint32_t* colors, const float* pos,
        uint32_t size, OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat);

    void ShaderEffectCreateRadialGradient(
        const OH_Drawing_Point2D* startPt, float startRadius, const OH_Drawing_Point2D* endPt, float endRadius,
        const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat);

    ~ShaderEffect() noexcept = default;

    OH_Drawing_ShaderEffect *get() const { return shaderEffect_.get(); }

private:
    UniqueNativeShaderEffect shaderEffect_;
};

} // namespace rnoh::drawing