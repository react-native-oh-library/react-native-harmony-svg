#include "RNSVGTextPathComponentInstance.h"
#include "Props.h"
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include "SvgTSpan.h"

namespace rnoh {
namespace svg {

RNSVGTextPathComponentInstance::RNSVGTextPathComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgTP);
}

void RNSVGTextPathComponentInstance::UpdateSpecialProps(SharedConcreteProps const &props) {
    m_svgTP->UpdateFontProps(props);
    m_svgTP->UpdateTextProps(props);
    m_svgTP->href_ = props->href;
    m_svgTP->startOffset_ = StringUtils::FromString(props->startOffset).ConvertToPx();
    m_svgTP->spacing_ = textPathSpacingFromStr(props->spacing);
    m_svgTP->midLine_ = textPathMidLineFromStr(props->midLine);
    m_svgTP->side_ = textPathSideFromStr(props->side);
    m_svgTP->method_ = textPathMethodFromStr(props->method);
}
} // namespace svg
} // namespace rnoh
