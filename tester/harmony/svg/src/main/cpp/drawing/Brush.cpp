#include "Brush.h"

namespace drawing {

Brush::Brush() : brush_(UniqueNativeBrush(OH_Drawing_BrushCreate(), &OH_Drawing_BrushDestroy)) {}

void Brush::SetAntiAlias(bool antiAlias) { OH_Drawing_BrushSetAntiAlias(brush_.get(), antiAlias); }

void Brush::SetColor(uint32_t color) { OH_Drawing_BrushSetColor(brush_.get(), color); }

void Brush::SetAlpha(uint8_t alpha) { OH_Drawing_BrushSetAlpha(brush_.get(), alpha); }

void Brush::Reset() { OH_Drawing_BrushReset(brush_.get()); }

} // namespace drawing
