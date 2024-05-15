#include "FontHolderBase.h"
namespace rnoh {
namespace svg {

void FontHolderBase::InheritFont(const std::shared_ptr<FontData> &parent, double scale) {
    if (fp_.Empty()) {
        // share parent font to save memory
        font_ = parent;
    } else {
        font_ = std::make_shared<FontData>(fp_, *parent, scale);
    }
}

} // namespace rnoh
} // namespace rnoh