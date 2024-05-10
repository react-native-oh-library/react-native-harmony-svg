#include "SvgText.h"
#include <memory>
#include <native_drawing/drawing_font_collection.h>

#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"
#include "SvgTSpan.h"

namespace rnoh {
void SvgText::OnDraw(OH_Drawing_Canvas *canvas) {
    for (auto const &child : children_) {
        auto tspan = std::dynamic_pointer_cast<SvgTSpan>(child);
        if (tspan) {
            if (tspan->fontSize == 0) {
                tspan->fontSize = fontSize;
            }
            if (tspan->x.empty()) {
                tspan->x = x;
            }
            if (tspan->y.empty()) {
                tspan->y = y;
            }
        }
    }
}

} // namespace rnoh