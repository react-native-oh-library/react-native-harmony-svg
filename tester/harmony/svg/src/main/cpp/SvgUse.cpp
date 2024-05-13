#include "SvgUse.h"
#include "SvgSymbol.h"

namespace rnoh {

void SvgUse::OnDraw(OH_Drawing_Canvas *canvas) {

    auto svgContext = GetContext();
    if(!svgContext) {
        LOG(INFO) << "[SvgUse::OnDraw] : svgContext is a null ptr";
        return;
    }

    auto refSvgNode = svgContext->GetSvgNodeById(href);
    if(!refSvgNode) {
        LOG(INFO) << "[SvgUse::OnDraw] : refSvgNode is a null ptr";
        return;
    }
    if (x != 0 || y != 0) {
        OH_Drawing_CanvasTranslate(canvas, vpToPx(x), vpToPx(y));
    }

    AttributeScope scope(refSvgNode);
    // LOG(INFO) << "[SvgUse::OnDraw] : childnode selfOpacity before inherit: " << refSvgNode->GetBaseAttributes().selfOpacity;
    // LOG(INFO) << "[SvgUse::OnDraw] : childnode opacity before inherit: " << refSvgNode->GetBaseAttributes().opacity;
    // LOG(INFO) << "[SvgUse::OnDraw] : use input opacity: " << attributes_.opacity;
    refSvgNode->InheritUseAttr(attributes_);
    // LOG(INFO) << "[SvgUse::OnDraw] : childnode selfOpacity after inherit: " << refSvgNode->GetBaseAttributes().selfOpacity;
    // LOG(INFO) << "[SvgUse::OnDraw] : childnode opacity after inherit: " << refSvgNode->GetBaseAttributes().selfOpacity;

    if (auto symbol = std::dynamic_pointer_cast<SvgSymbol>(refSvgNode)) {
        LOG(INFO) << "[SvgUse::OnDraw] : svgSymbol component ";
        LOG(INFO) << "[SvgUse::OnDraw] : input width: " << width << "input height: " << height;
        symbol->drawSymbol(canvas, width, height);
        refSvgNode->Draw(canvas);
    } else {
        LOG(INFO) << "[SvgUse::OnDraw] : normal component";
        refSvgNode->Draw(canvas);
    }
    return;
}

SvgUse::AttributeScope::AttributeScope(const std::shared_ptr<SvgNode>& node) : node_(node)
{
    auto nodeAttr = node->GetBaseAttributes();
    attributes_ = nodeAttr;
}

SvgUse::AttributeScope::~AttributeScope()
{
    //TODO : check null ptr
    node_->SetBaseAttributes(attributes_);
} 

}