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
        font_ = std::make_shared<FontData>(fp_, FontData{}, scale_);
    }
    for (auto &child : children_) {
        if (auto childG = std::dynamic_pointer_cast<SvgGroup>(child)) {
            childG->InheritFont(font_);
        }
    }
}

void SvgGroup::InheritFont(const std::shared_ptr<FontData> &parent) {
    if (fp_.Empty()) {
        // share parent font to save memory
        font_ = parent;
    } else {
        font_ = std::make_shared<FontData>(fp_, *parent, scale_);
    }
}
} // namespace rnoh