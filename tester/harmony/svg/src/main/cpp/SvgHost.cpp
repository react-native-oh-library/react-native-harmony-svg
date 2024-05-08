#include "SvgHost.h"
namespace rnoh {
void SvgHost::OnChildInsertCommon(const std::shared_ptr<SvgHost> &childSvgHost) {
    if (!childSvgHost) {
        return;
    }
    GetSvgNode()->AppendChild(childSvgHost->GetSvgNode());
}
} // namespace rnoh