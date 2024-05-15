#include "SvgTextPath.h"
#include "SvgTSpan.h"
namespace rnoh {
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

OH_Drawing_Path *SvgTextPath::getTextPath() {
    auto node = context_->GetSvgNodeById(href_);
    if (node) {
        return node->AsPath();
    }
    LOG(INFO) << "TEXT_PATH ref node missing, href = " << href_;
    return nullptr;
}
} // namespace rnoh
