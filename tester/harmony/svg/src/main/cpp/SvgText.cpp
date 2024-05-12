#include "SvgText.h"
#include <memory>
#include <native_drawing/drawing_font_collection.h>

#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"
#include "SvgTSpan.h"

namespace rnoh {
void SvgText::OnDraw(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        auto* rect = OH_Drawing_RectCreate(0, 0, 0, 0);
        OH_Drawing_CanvasGetLocalClipBounds(canvas, rect);
        glyphCtx_ = std::make_shared<GlyphContext>(scale_, OH_Drawing_RectGetWidth(rect), OH_Drawing_RectGetHeight(rect));
        LOG(INFO) << "clip width = " << OH_Drawing_RectGetWidth(rect) << " clip height = " << OH_Drawing_RectGetHeight(rect);
        OH_Drawing_RectDestroy(rect);
    }
    glyphCtx_->pushContext(true, shared_from_this(), {}, x_, y_, dx_, dy_, rotate_);
    for (auto const &child : children_) {
        auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child);
        if (!tSpan) {
            continue;
        }
        if (tSpan->fontSize == 0) {
            tSpan->fontSize = fontSize;
        }
        // if (tSpan->x.empty()) {
        //     tSpan->x = x;
        // }
        // if (tSpan->y.empty()) {
        //     tSpan->y = y;
        // }
        tSpan->SetContext(glyphCtx_);
    }
}
} // namespace rnoh