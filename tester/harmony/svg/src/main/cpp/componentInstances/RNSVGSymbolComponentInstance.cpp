#include "RNSVGSymbolComponentInstance.h"
#include "SvgSymbol.h"

namespace rnoh {
namespace svg {

RNSVGSymbolComponentInstance::RNSVGSymbolComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    DLOG(INFO) << "[RNSVGSymbolComponentInstance] init";
    SetSvgNode(std::make_shared<SvgSymbol>());
}

void RNSVGSymbolComponentInstance::UpdateElementProps(SharedConcreteProps const &props) {
    auto svgSymbol = std::dynamic_pointer_cast<SvgSymbol>(GetSvgNode());
    svgSymbol->UpdateCommonProps(props);
    // set attribute to svgSymbol.
    svgSymbol->mMinX = props->minX;
    svgSymbol->mMinY = props->minY;
    svgSymbol->mVbWidth = props->vbWidth;
    svgSymbol->mVbHeight = props->vbHeight;
    svgSymbol->mMeetOrSlice = props->meetOrSlice;
    svgSymbol->mAlign = props->align;

    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] minX: " << props->minX;
    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] minY: " << props->minY;
    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] vbWidth: " << props->vbWidth;
    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] vbHeight: " << props->vbHeight;
    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] mMeetOrSlice: " << props->meetOrSlice;
    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] mAlign: " << props->align;
    DLOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] opacity: " << props->opacity;
}

} // namespace svg
} // namespace rnoh
