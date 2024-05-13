#include "RNSVGSymbolComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "utils/StringUtils.h"

namespace rnoh {

RNSVGSymbolComponentInstance::RNSVGSymbolComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    LOG(INFO) << "[RNSVGSymbolComponentInstance] init" ;
    SetSvgNode(std::make_shared<SvgSymbol>());
}

void RNSVGSymbolComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    CppComponentInstance::onPropsChanged(props);
    GetSvgNode()->UpdateCommonProps(props);
    LOG(INFO) << "[RNSVGSymbolComponentInstance] minX: " << props->minX;
    LOG(INFO) << "[RNSVGSymbolComponentInstance] minY: " << props->minY;
    LOG(INFO) << "[RNSVGSymbolComponentInstance] vbWidth: " << props->vbWidth;
    LOG(INFO) << "[RNSVGSymbolComponentInstance] vbHeight: " << props->vbHeight;
    LOG(INFO) << "[RNSVGSymbolComponentInstance] mAlign: " << props->align;
    LOG(INFO) << "[RNSVGSymbolComponentInstance] meetOrSlice: " << props->meetOrSlice;
    // set attribute to svgSymbol
    auto svgSymbol = std::dynamic_pointer_cast<SvgSymbol>(GetSvgNode());
    svgSymbol->mMinX = props->minX;
    svgSymbol->mMinY = props->minY;
    svgSymbol->mVbHeight = props->vbWidth;
    svgSymbol->mVbHeight = props->vbHeight;
    svgSymbol->mMeetOrSlice = props->meetOrSlice;
    svgSymbol->mAlign = props->align;
    // svgSymbol->viewBox = Rect(props->minX, props->minY, props->vbWidth, props->vbHeight);
    GetSvgNode()->UpdateCommonProps(props);
}

SvgArkUINode &RNSVGSymbolComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

} // namespace rnoh
