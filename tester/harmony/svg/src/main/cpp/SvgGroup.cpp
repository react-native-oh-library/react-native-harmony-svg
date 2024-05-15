#include "SvgGroup.h"
namespace rnoh {
void SvgGroup::InitGroupFlag() {
    hrefFill_ = true;
    hrefRender_ = true;
    passStyle_ = true;
    inheritStyle_ = true;
    drawTraversed_ = true;
}

void SvgGroup::OnInitStyle() {
    if (!font_) {
        InitFont(scale_);
    }
    for (auto &child : children_) {
        if (auto childG = std::dynamic_pointer_cast<FontHolderBase>(child)) {
            childG->InheritFont(font_, child->GetScale());
        }
    }
}

} // namespace rnoh