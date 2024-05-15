#include "TextBase.h"
namespace rnoh {
void TextBase::InitGlyph(OH_Drawing_Canvas *canvas, double scale) {
    auto rect = std::unique_ptr<OH_Drawing_Rect, decltype(&OH_Drawing_RectDestroy)>(OH_Drawing_RectCreate(0, 0, 0, 0),
                                                                                    OH_Drawing_RectDestroy);
    OH_Drawing_CanvasGetLocalClipBounds(canvas, rect.get());
    glyphCtx_ = std::make_shared<GlyphContext>(scale, OH_Drawing_RectGetWidth(rect.get()),
                                               OH_Drawing_RectGetHeight(rect.get()));
}
} // namespace rnoh