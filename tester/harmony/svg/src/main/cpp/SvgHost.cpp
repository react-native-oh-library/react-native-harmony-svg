#include "SvgHost.h"
namespace rnoh {
void SvgHost::OnChildInsertCommon(
    const std::shared_ptr<SvgHost>& childSvgHost) {
    if (!childSvgHost) {
        return;
    }
    auto child = childSvgHost->GetSvgNode();
    child->SetContext(GetSvgNode()->GetContext());
    GetSvgNode()->AppendChild(child);
}
}