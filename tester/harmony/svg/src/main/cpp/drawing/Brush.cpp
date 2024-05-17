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

void Brush::Reset() { OH_Drawing_BrushReset(brush_.get()); }

} // namespace rnoh::drawing
