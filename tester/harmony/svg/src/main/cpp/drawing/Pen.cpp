#include "Pen.h"

namespace drawing {

Pen::Pen() : pen_(UniqueNativePen(OH_Drawing_PenCreate(), &OH_Drawing_PenDestroy)) {}

void Pen::SetAntiAlias(bool antiAlias) { OH_Drawing_PenSetAntiAlias(pen_.get(), antiAlias); }

void Pen::SetColor(uint32_t color) { OH_Drawing_PenSetColor(pen_.get(), color); }

void Pen::SetAlpha(uint8_t alpha) { OH_Drawing_PenSetAlpha(pen_.get(), alpha); }

void Pen::SetWidth(double width) { OH_Drawing_PenSetWidth(pen_.get(), width); }

void Pen::SetMiterLimit(float miterLimit) { OH_Drawing_PenSetMiterLimit(pen_.get(), miterLimit); }

void Pen::SetLineCap(LineCapStyle lineCap) { OH_Drawing_PenSetCap(pen_.get(), lineCap); }

void Pen::SetLineJoin(LineJoinStyle lineJoin) { OH_Drawing_PenSetJoin(pen_.get(), lineJoin); }

void Pen::Reset() {}

} // namespace drawing