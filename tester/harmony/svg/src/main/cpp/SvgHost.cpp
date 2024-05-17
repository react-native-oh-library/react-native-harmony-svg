#include "SvgHost.h"
namespace rnoh {
namespace svg {
    
void SvgHost::OnChildInsertCommon(const std::shared_ptr<SvgHost> &childSvgHost) {
    if (!childSvgHost) {
        return;
    }
    GetSvgNode()->AppendChild(childSvgHost->GetSvgNode());
}

void SvgHost::OnChildRemoveCommon(const std::shared_ptr<SvgHost> &childSvgHost) {
    if (!childSvgHost) {
        return;
    }
    GetSvgNode()->removeChild(childSvgHost->GetSvgNode());
}

} // namespace svg
} // namespace rnoh