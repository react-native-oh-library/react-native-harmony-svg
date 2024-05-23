#include "SvgNode.h"
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_path.h>
#include <regex>
#include <string>
#include "properties/SvgDomType.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"
#include "utils/SvgAttributesParser.h"
#include "utils/Utils.h"
#include "utils/StringUtils.h"
#include "utils/SvgAttributesParser.h"
#include "SvgGradient.h"
#include "SvgPattern.h"

namespace rnoh {
namespace svg {

void SvgNode::InitStyle(const SvgBaseAttribute &attr) {
    InheritAttr(attr);
    if (hrefFill_) {
        auto fillHref = attributes_.fillState.GetHref();
        if (!fillHref.empty()) {
            auto gradient = GetGradient(fillHref);
            if (gradient) {
                attributes_.fillState.SetGradient(gradient.value(), true);
            }
            auto pattern = GetPatternAttr(fillHref);
            if (pattern) {
                attributes_.fillState.SetPattern(pattern);
            }
        }
        auto strokeHref = attributes_.strokeState.GetHref();
        if (!strokeHref.empty()) {
            auto gradient = GetGradient(strokeHref);
            if (gradient) {
                attributes_.strokeState.SetGradient(gradient.value(), true);
            }
        }
    }
    OnInitStyle();
    if (passStyle_) {
        for (auto &node : children_) {
            // pass down style only if child inheritStyle_ is true
            node->InitStyle((node->inheritStyle_) ? attributes_ : SvgBaseAttribute());
        }
    }
}

void SvgNode::OnDrawTraversed(OH_Drawing_Canvas *canvas) {
    auto smoothEdge = GetSmoothEdge();
    for (auto &node : children_) {
        if (node && node->drawTraversed_) {
            if (GreatNotEqual(smoothEdge, 0.0f)) {
                node->SetSmoothEdge(smoothEdge);
            }
            node->Draw(canvas);
        }
    }
}

const Rect &SvgNode::GetRootViewBox() const {
    if (!context_) {
        //         LOGE("Gradient failed, svgContext is null");
        static Rect empty;
        return empty;
    }
    return context_->GetRootViewBox();
}

void SvgNode::OnClipPath(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[SvgNode] Draw OnClipPath enter";
    if (!context_) {
        LOG(WARNING) << "[SvgNode] OnClipPath: Context is null!";
        return;
    }
    auto refSvgNode = context_->GetSvgNodeById(hrefClipPath_);
    if (!refSvgNode) {
        LOG(WARNING) << "[SvgNode] OnClipPath: SvgNode is null!";
        return;
    };
    auto clipPath = refSvgNode->AsPath();

    // TODO: maybe return optional from AsPath?
    // if (!clipPath) {
    //     LOG(WARNING) << "[SvgNode] OnClipPath: Path is null!";
    //     return;
    // };

    // Set clipRule through Drawing API
    clipPath.SetFillType(attributes_.clipState.GetClipRuleForDraw());
    OH_Drawing_CanvasClipPath(canvas, clipPath.get(), OH_Drawing_CanvasClipOp::INTERSECT, true);
}

void SvgNode::OnMask(OH_Drawing_Canvas *canvas) {
    if (!context_) {
        LOG(INFO) << "NO CONTEXT";
        return;
    }
    auto refMask = context_->GetSvgNodeById(attributes_.maskId);
    if (!refMask) {
        return;
    };
    refMask->Draw(canvas);
}

void SvgNode::OnTransform(OH_Drawing_Canvas *canvas) {
    // input transfrom: (float scaleX, float skewY, float skewX, float scaleY, float transX, float transY)
    const auto &transform = attributes_.transform;
    /*
    /* (OH_Drawing_Matrix* , float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float
    persp0, float persp1, float persp2 )
    */
    if (!attributes_.strokeState.GetVectorEffect() && transform.size() > 5) {
        cTM_.SetMatrix(transform[0], transform[2], transform[4] * scale_, transform[1], transform[3],
                       transform[5] * scale_, 0, 0, 1.0);
        OH_Drawing_CanvasConcatMatrix(canvas, cTM_.get());
    }
}

std::optional<Gradient> SvgNode::GetGradient(const std::string &href) {
    if (!context_) {
        LOG(INFO) << "NO CONTEXT";
        return std::nullopt;
    }
    auto refSvgNode = context_->GetSvgNodeById(href);
    CHECK_NULL_RETURN(refSvgNode, std::nullopt);
    auto svgGradient = std::dynamic_pointer_cast<SvgGradient>(refSvgNode);
    if (svgGradient) {
        return std::make_optional(svgGradient->GetGradient());
    }
    return std::nullopt;
}

std::shared_ptr<PatternAttr> SvgNode::GetPatternAttr(const std::string &href) {
    if (!context_) {
        LOG(INFO) << "NO CONTEXT";
        return nullptr;
    }
    auto refSvgNode = context_->GetSvgNodeById(href);
    CHECK_NULL_RETURN(refSvgNode, nullptr);
    auto svgPattern = std::dynamic_pointer_cast<SvgPattern>(refSvgNode);
    if (svgPattern) {
        return svgPattern->GetPatternAttr();
    }
    return nullptr;
}

void SvgNode::Draw(OH_Drawing_Canvas *canvas) {
    if (!display_) {
        return;
    }
    // mask and filter create extra layers, need to record initial layer count
    const auto count = OH_Drawing_CanvasGetSaveCount(canvas);
    OH_Drawing_CanvasSave(canvas);
    if (!hrefClipPath_.empty()) {
        OnClipPath(canvas);
    }
    if (!attributes_.transform.empty()) {
        OnTransform(canvas);
    }
    if (!attributes_.maskId.empty()) {
        OnMask(canvas);
    }

    OH_Drawing_CanvasGetTotalMatrix(canvas, lastCanvasMatrix_.get());

    OnDraw(canvas);
    // on marker

    OnDrawTraversed(canvas);
    OH_Drawing_CanvasRestoreToCount(canvas, count);
}

void SvgNode::UpdateCommonProps(const ConcreteProps &props) {
    attributes_.id = props->name;
    display_ = props->display != "none";

    if (hrefRender_) {
        attributes_.transform = props->matrix;
        attributes_.maskId = props->mask;
        attributes_.selfOpacity = props->opacity;
        attributes_.markerStart = props->markerStart;
        attributes_.markerMid = props->markerMid;
        attributes_.markerEnd = props->markerEnd;
        // clipPath
        attributes_.clipPath = props->clipPath;
        hrefClipPath_ = props->clipPath;
    }

    std::unordered_set<std::string> set;
    for (const auto &prop : props->propList) {
        set.insert(prop);
    }
    
    if (props->fill.type == 1) {
        attributes_.fillState.SetHref(props->fill.brushRef);
    } else if (props->fill.type == 2) {
        Color color = Color((uint32_t)*props->fill.payload);
        color.SetUseCurrentColor(true);
        attributes_.fillState.SetColor(color, true);
    } else if (facebook::react::isColorMeaningful(props->fill.payload)) {
        attributes_.fillState.SetColor(Color((uint32_t)*props->fill.payload), set.count("fill"));
    } else {
        attributes_.fillState.SetColor(Color::TRANSPARENT, set.count("fill"));
    }
    
    if (props->stroke.type == 1) {
        attributes_.strokeState.SetHref(props->stroke.brushRef);
    } else if (props->stroke.type == 2) {
        Color color = Color((uint32_t)*props->stroke.payload);
        color.SetUseCurrentColor(true);
        attributes_.strokeState.SetColor(color, true);
    } else if (facebook::react::isColorMeaningful(props->stroke.payload)) {
        attributes_.strokeState.SetColor(Color((uint32_t)*props->stroke.payload), set.count("stroke"));
    } else {
        attributes_.strokeState.SetColor(Color::TRANSPARENT, set.count("stroke"));
    }
    attributes_.fillState.SetOpacity(std::clamp(props->fillOpacity, 0.0, 1.0), set.count("fillOpacity"));
    // todo Inheritance situation
    attributes_.fillState.SetFillRule(static_cast<FillState::FillRule>(props->fillRule), true);
    attributes_.strokeState.SetLineWidth(vpToPx(StringUtils::StringToDouble(props->strokeWidth)),
                                         set.count("strokeWidth"));
    attributes_.strokeState.SetStrokeDashArray(StringUtils::stringVectorToDoubleVector(props->strokeDasharray),
                                               set.count("strokeDasharray"));
    attributes_.strokeState.SetStrokeDashOffset(vpToPx(props->strokeDashoffset), set.count("strokeDashoffset"));
    attributes_.strokeState.SetLineCap(SvgAttributesParser::GetLineCapStyle(std::to_string(props->strokeLinecap)),
                                       set.count("strokeLinecap"));
    attributes_.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(std::to_string(props->strokeLinejoin)),
                                        set.count("strokeLinejoin"));
    attributes_.strokeState.SetVectorEffect(props->vectorEffect);
    auto limit = vpToPx(props->strokeMiterlimit);
    if (GreatOrEqual(limit, 1.0)) {
        attributes_.strokeState.SetMiterLimit(limit, set.count("strokeMiterlimit"));
    }
    attributes_.strokeState.SetOpacity(std::clamp(props->strokeOpacity, 0.0, 1.0), set.count("strokeOpacity"));
    attributes_.clipState.SetClipRule(static_cast<ClipState::ClipRule>(props->clipRule), true);
}

Rect SvgNode::AsBounds() {
    auto path = AsPath();
    auto ohRect = path.GetBounds();
    float x = ohRect.GetLeft();
    float y = ohRect.GetTop();
    float width = ohRect.GetWidth();
    float height = ohRect.GetHeight();
    auto rect = Rect(x, y, width, height);
    return rect;
}

void SvgNode::ContextTraversal() {
    if (!context_) {
        LOG(INFO) << "NO CONTEXT";
        return;
    }
    if (!attributes_.id.empty()) {
        context_->Push(attributes_.id, shared_from_this());
    }
    for (const auto &child : children_) {
        child->SetContext(context_);
        child->ContextTraversal();
    }
}

double SvgNode::relativeOnWidth(Dimension length) { return length.ConvertToPx(getCanvasWidth()); }

double SvgNode::relativeOnHeight(Dimension length) { return length.ConvertToPx(getCanvasHeight()); }

double SvgNode::relativeOnOther(Dimension length) { return length.ConvertToPx(getCanvasDiagonal()); }

double SvgNode::getCanvasWidth() {
    if (canvasWidth_ != -1) {
        return canvasWidth_;
    }
    // TODO if root is text root
    if (context_->getCanvasBounds().IsValid()) {
        canvasWidth_ = context_->getCanvasBounds().Width();
        return canvasWidth_;
    }
    return 0;
}

double SvgNode::getCanvasHeight() {
    if (canvasHeight_ != -1) {
        return canvasHeight_;
    }
    // TODO if root is text root
    if (context_->getCanvasBounds().IsValid()) {
        canvasHeight_ = context_->getCanvasBounds().Height();
        return canvasHeight_;
    }
    return 0;
}

double SvgNode::getCanvasDiagonal() {
    if (canvasDiagonal_ != -1) {
        return canvasDiagonal_;
    }
    double powX = pow((getCanvasWidth()), 2);
    double powY = pow((getCanvasHeight()), 2);
    canvasDiagonal_ = sqrt(powX + powY) * M_SQRT1_2l;
    return canvasDiagonal_;
}

} // namespace svg
} // namespace rnoh