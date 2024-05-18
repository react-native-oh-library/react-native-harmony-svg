#include "Brush.h"

namespace rnoh::drawing {

Brush::Brush() : brush_(UniqueNativeBrush(OH_Drawing_BrushCreate(), &OH_Drawing_BrushDestroy)) {}

Brush::Brush(Brush const &other) : brush_(UniqueNativeBrush(OH_Drawing_BrushCopy(other.brush_.get()), &OH_Drawing_BrushDestroy)) {}

Brush &Brush::operator=(Brush const &) {
    brush_ = UniqueNativeBrush(OH_Drawing_BrushCopy(brush_.get()), &OH_Drawing_BrushDestroy);
    return *this;
}

void Brush::SetAntiAlias(bool antiAlias) { OH_Drawing_BrushSetAntiAlias(brush_.get(), antiAlias); }

void Brush::SetColor(uint32_t color) { OH_Drawing_BrushSetColor(brush_.get(), color); }

void Brush::SetAlpha(uint8_t alpha) { OH_Drawing_BrushSetAlpha(brush_.get(), alpha); }

void Brush::SetLinearShaderEffect(const OH_Drawing_Point2D* startPt, const OH_Drawing_Point2D* endPt,
    const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat) {
    brushShaderEffect_.ShaderEffectCreateLinearGradient(startPt, endPt, colors, pos, size, mode, mat);
    OH_Drawing_BrushSetShaderEffect(brush_.get(), brushShaderEffect_.get());
}

void Brush::SetRadialShaderEffect(const OH_Drawing_Point2D* startPt, float startRadius,
    const OH_Drawing_Point2D* endPt, float endRadius, const uint32_t* colors, const float* pos, uint32_t size,
    OH_Drawing_TileMode mode, const OH_Drawing_Matrix* mat) {
    brushShaderEffect_.ShaderEffectCreateRadialGradient(
        startPt, startRadius, endPt,endRadius, colors, pos, size, mode, mat);
    OH_Drawing_BrushSetShaderEffect(brush_.get(), brushShaderEffect_.get());
}

void Brush::SetImageShaderEffect(OH_Drawing_Image* image, OH_Drawing_TileMode tileX,
    OH_Drawing_TileMode tileY, const OH_Drawing_SamplingOptions* opt, const OH_Drawing_Matrix* mat) {
    brushShaderEffect_.ShaderEffectCreateImageShader(image, tileX, tileY, opt, mat);
    OH_Drawing_BrushSetShaderEffect(brush_.get(), brushShaderEffect_.get());
}

void Brush::Reset() { OH_Drawing_BrushReset(brush_.get()); }

} // namespace rnoh::drawing
