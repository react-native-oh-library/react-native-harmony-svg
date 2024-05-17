#include "TextBase.h"
#include "drawing/Rect.h"

namespace rnoh {
namespace svg {

void TextBase::InitGlyph(OH_Drawing_Canvas *canvas, double scale) {
    drawing::Rect rect;
    OH_Drawing_CanvasGetLocalClipBounds(canvas, rect.get());
    glyphCtx_ = std::make_shared<GlyphContext>(scale, rect.GetWidth(), rect.GetHeight());
}

} // namespace svg
} // namespace rnoh