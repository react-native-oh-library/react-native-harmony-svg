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
        OH_Drawing_CanvasTranslate(canvas, x, y);
    }
    

    AttributeScope scope(refSvgNode);

    refSvgNode->InheritUseAttr(attributes_);
    if (std::dynamic_pointer_cast<SvgSymbol>(refSvgNode) != nullptr) {
        LOG(INFO) << "[SvgUse::OnDraw] : svgSymbol drawSymbol ";
        SvgSymbol svgSymbol = static_cast<SvgSymbol>(refSvgNode);
        svgSymbol.drawSymbol(canvas, width, height);
    } else {
        LOG(INFO) << "[SvgUse::OnDraw] : Draw";
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