#include "RNSVGSymbolComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "utils/StringUtils.h"

namespace rnoh {
namespace svg {

RNSVGSymbolComponentInstance::RNSVGSymbolComponentInstance(Context context)  : RNSVGBaseComponentInstance(std::move(context)) {
    LOG(INFO) << "[RNSVGSymbolComponentInstance] init" ;
    SetSvgNode(std::make_shared<SvgSymbol>());
}

void RNSVGSymbolComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
     
    
    auto svgSymbol = std::dynamic_pointer_cast<SvgSymbol>(GetSvgNode());
    // set attribute to svgMask.
    svgSymbol->mMinX = props->minX;
    svgSymbol->mMinY = props->minY;
    svgSymbol->mVbWidth = props->vbWidth;
    svgSymbol->mVbHeight = props->vbHeight;
    svgSymbol->mMeetOrSlice = props->meetOrSlice;
    svgSymbol->mAlign = props->align;
    
    LOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] minX: " << props->minX;
    LOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] minY: " << props->minY;
    LOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] vbWidth: " << props->vbWidth;
    LOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] vbHeight: " << props->vbHeight;
    LOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] mMeetOrSlice: " << props->meetOrSlice;
    LOG(INFO) << "[SvgSymbol RNSVGSymbolComponentInstance] mAlign: " << props->align;
    // set attribute to svgSymbol
    //auto svgSymbol = std::dynamic_pointer_cast<SvgSymbol>(GetSvgNode());
   // svgSymbol->viewBox = Rect(props->minX, props->minY, props->vbWidth, props->vbHeight);
     
}


} // namespace svg
} // namespace rnoh
