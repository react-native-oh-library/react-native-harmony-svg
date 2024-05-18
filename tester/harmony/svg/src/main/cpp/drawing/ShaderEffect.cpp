#include "ShaderEffect.h"

namespace rnoh::drawing {

ShaderEffect::ShaderEffect() : shaderEffect_(UniqueNativeShaderEffect(nullptr, &OH_Drawing_ShaderEffectDestroy)) {}

void ShaderEffect::ShaderEffectCreateLinearGradient(const OH_Drawing_Point2D* startPt, const OH_Drawing_Point2D* endPt,
    const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat) {
    shaderEffect_ = UniqueNativeShaderEffect(
        OH_Drawing_ShaderEffectCreateLinearGradientWithLocalMatrix(startPt, endPt, colors, pos, size, mode, mat),
        &OH_Drawing_ShaderEffectDestroy);
}

void ShaderEffect::ShaderEffectCreateRadialGradient(const OH_Drawing_Point2D* startPt, float startRadius,
    const OH_Drawing_Point2D* endPt, float endRadius, const uint32_t* colors, const float* pos, uint32_t size,
    OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat) {
    shaderEffect_ = UniqueNativeShaderEffect(
        OH_Drawing_ShaderEffectCreateTwoPointConicalGradient(startPt, startRadius, endPt, endRadius, colors, pos, size,
            mode, mat), &OH_Drawing_ShaderEffectDestroy);
}

void ShaderEffect::ShaderEffectCreateImageShader(OH_Drawing_Image* image, OH_Drawing_TileMode tileX,
    OH_Drawing_TileMode tileY, const OH_Drawing_SamplingOptions* opt, const OH_Drawing_Matrix* mat) {
    shaderEffect_ = UniqueNativeShaderEffect(
        OH_Drawing_ShaderEffectCreateImageShader(image, tileX, tileY, opt, mat), &OH_Drawing_ShaderEffectDestroy);
}

} // namespace rnoh::drawing
