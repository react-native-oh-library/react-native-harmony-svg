#include "SvgText.h"
#include <memory>
#include <native_drawing/drawing_font_collection.h>

#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"
#include "SvgTSpan.h"

namespace rnoh {
void SvgText::GlyphTraversal(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        InitGlyph(canvas);
    }
    for (auto const &child : children_) {
        auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child);
        if (!tSpan) {
            continue;
        }
        tSpan->SetContext(glyphCtx_);
    }
}
void SvgText::OnDraw(OH_Drawing_Canvas *canvas) {
    GlyphTraversal(canvas);
    glyphCtx_->pushContext(true, shared_from_this(), x_, y_, dx_, dy_, rotate_);
}

void SvgText::InitGlyph(OH_Drawing_Canvas *canvas) {
    auto rect = std::unique_ptr<OH_Drawing_Rect, decltype(&OH_Drawing_RectDestroy)>(OH_Drawing_RectCreate(0, 0, 0, 0),
                                                                                    OH_Drawing_RectDestroy);
    // auto *rect = OH_Drawing_RectCreate(0, 0, 0, 0);
    OH_Drawing_CanvasGetLocalClipBounds(canvas, rect.get());
    glyphCtx_ = std::make_shared<GlyphContext>(scale_, OH_Drawing_RectGetWidth(rect.get()),
                                               OH_Drawing_RectGetHeight(rect.get()));
}
} // namespace rnoh