#include "SvgText.h"
#include <memory>
#include <native_drawing/drawing_font_collection.h>

#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"
#include "SvgTSpan.h"

namespace rnoh {
void SvgText::OnDraw(OH_Drawing_Canvas *canvas) {
    Offset pos;
    for (auto const &child : children_) {
        auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child);
        if (!tSpan) {
            continue;
        }
        if (tSpan->fontSize == 0) {
            tSpan->fontSize = fontSize;
        }
        if (tSpan->x.empty()) {
            tSpan->x = x;
        }
        if (tSpan->y.empty()) {
            tSpan->y = y;
        }
        pos = tSpan->DrawText(canvas, pos);
    }
}

} // namespace rnoh