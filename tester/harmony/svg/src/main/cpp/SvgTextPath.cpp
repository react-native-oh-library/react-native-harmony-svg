#include "SvgTextPath.h"
#include "SvgTSpan.h"

namespace rnoh {
namespace svg {

void SvgTextPath::OnDraw(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        InitGlyph(canvas, scale_);
    }
    for (auto const &child : children_) {
        if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child)) {
            tSpan->SetGlyphContext(glyphCtx_);
            tSpan->SetTextPathRef(std::dynamic_pointer_cast<SvgTextPath>(shared_from_this()));
        }
    }
}

drawing::Path SvgTextPath::getTextPath() {
    auto node = context_->GetSvgNodeById(href_);
    if (node) {
        return node->AsPath();
    }
    DLOG(INFO) << "TEXT_PATH ref node missing, href = " << href_;
    return drawing::Path();
}

} // namespace svg
} // namespace rnoh