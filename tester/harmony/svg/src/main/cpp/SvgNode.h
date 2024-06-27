// from ArkUI "frameworks/core/components_ng/svg/parse/svg_node.h"
#pragma once

#include <memory>
#include <vector>
#include "SvgBaseAttribute.h"
#include "SvgContext.h"
#include "properties/Decoration.h"
#include "properties/Dimension.h"
#include "properties/Size.h"
#include "Props.h"
#include "drawing/Path.h"
#include "utils/StringUtils.h"
#include "utils/SvgAttributesParser.h"
#include <glog/logging.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_rect.h>

namespace rnoh {
namespace svg {

class SvgNode : public std::enable_shared_from_this<SvgNode> {
public:
    SvgNode() = default;
    virtual ~SvgNode() = default;

    std::shared_ptr<SvgContext> GetContext() { return context_; }
    void SetContext(std::shared_ptr<SvgContext> context) { context_ = context; }

    void ContextTraversal();
    void InitStyle(const SvgBaseAttribute &attr);

    virtual void Draw(OH_Drawing_Canvas *canvas);

    virtual drawing::Path AsPath() {
        DLOG(INFO) << "[SVGNode] AsPath";
        return drawing::Path();
    };

    SvgBaseAttribute GetBaseAttributes() const { return attributes_; }

    void SetBaseAttributes(const SvgBaseAttribute &attr) { attributes_ = attr; }

    virtual void AppendChild(const std::shared_ptr<SvgNode> &child) { children_.emplace_back(child); }

    virtual void removeChild(const std::shared_ptr<SvgNode> &child) {
        auto it = std::find(children_.begin(), children_.end(), child);
        if (it != children_.end()) {
            children_.erase(it);
        }
    }

    template <typename ConcreteProps> void UpdateHrefRenderProps(const std::shared_ptr<ConcreteProps> &props) {
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
    }

    template <typename ConcreteProps> void UpdateCommonProps(const std::shared_ptr<ConcreteProps> &props) {
        UpdateHrefRenderProps(props);
        std::unordered_set<std::string> set;
        for (const auto &prop : props->propList) {
            set.insert(prop);
        }

        if (props->fill.type == 2) {
            Color color = Color((uint32_t)*props->fill.payload);
            color.SetUseCurrentColor(true);
            attributes_.fillState.SetColor(color, true);
        } else if (facebook::react::isColorMeaningful(props->fill.payload)) {
            attributes_.fillState.SetColor(Color((uint32_t)*props->fill.payload), set.count("fill"));
        } else {
            attributes_.fillState.SetColor(Color::TRANSPARENT, set.count("fill"));
        }
        attributes_.fillState.SetHref(props->fill.brushRef);

        if (props->stroke.type == 2) {
            Color color = Color((uint32_t)*props->stroke.payload);
            color.SetUseCurrentColor(true);
            attributes_.strokeState.SetColor(color, true);
        } else if (facebook::react::isColorMeaningful(props->stroke.payload)) {
            attributes_.strokeState.SetColor(Color((uint32_t)*props->stroke.payload), set.count("stroke"));
        } else {
            attributes_.strokeState.SetColor(Color::TRANSPARENT, set.count("stroke"));
        }
        attributes_.strokeState.SetHref(props->stroke.brushRef);

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
        attributes_.strokeState.SetLineJoin(
            SvgAttributesParser::GetLineJoinStyle(std::to_string(props->strokeLinejoin)), set.count("strokeLinejoin"));
        attributes_.strokeState.SetVectorEffect(props->vectorEffect);
        auto limit = vpToPx(props->strokeMiterlimit);
        if (GreatOrEqual(limit, 1.0)) {
            attributes_.strokeState.SetMiterLimit(limit, set.count("strokeMiterlimit"));
        }
        attributes_.strokeState.SetOpacity(std::clamp(props->strokeOpacity, 0.0, 1.0), set.count("strokeOpacity"));
        attributes_.clipState.SetClipRule(static_cast<ClipState::ClipRule>(props->clipRule), true);
    }

    virtual Rect AsBounds();

    void SetScale(const double &scale) { scale_ = scale; }

    double GetScale() const { return scale_; }

    void InheritAttr(const SvgBaseAttribute &parent) {
        attributes_.Inherit(parent);
        // svg color -> current color
        if (attributes_.strokeState.GetColor().IsUseCurrentColor()) {
            attributes_.strokeState.SetColor(context_->GetSvgColor(), true);
        }
        if (attributes_.fillState.GetColor().IsUseCurrentColor()) {
            attributes_.fillState.SetColor(context_->GetSvgColor(), true);
        }
    }

    void InheritUseAttr(const SvgBaseAttribute &parent) { attributes_.InheritFromUse(parent); }

    drawing::Matrix lastCanvasMatrix_;

    double relativeOnWidth(Dimension length);
    double relativeOnHeight(Dimension length);
    double relativeOnOther(Dimension length);

    double getCanvasWidth();
    double getCanvasHeight();
    double getCanvasDiagonal();

protected:
    // override as need by derived class
    // called by function AppendChild
    virtual void OnAppendChild(const std::shared_ptr<SvgNode> &child) {}
    // called by function InitStyle
    virtual void OnInitStyle() {}

    virtual void OnDraw(OH_Drawing_Canvas *canvas) {}
    virtual void OnDrawTraversed(OH_Drawing_Canvas *canvas);
    void OnClipPath(OH_Drawing_Canvas *canvas);
    void OnMask(OH_Drawing_Canvas *canvas);
    void OnTransform(OH_Drawing_Canvas *canvas);

    const Rect &GetRootViewBox() const;

    void SetSmoothEdge(float edge) { attributes_.smoothEdge = edge; }
    float GetSmoothEdge() const { return attributes_.smoothEdge; }

    std::optional<Gradient> GetGradient(const std::string &href);

    std::shared_ptr<PatternAttr> GetPatternAttr(const std::string &href);

    void InitNoneFlag() {
        hrefFill_ = false;
        hrefRender_ = false;
        passStyle_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    SvgBaseAttribute attributes_;

    std::shared_ptr<SvgContext> context_;

    std::vector<std::shared_ptr<SvgNode>> children_;

    std::string hrefClipPath_;
    std::string imagePath_;

    // TODO get densityPixels in CAPI
    double scale_ = 3.25;

    drawing::Matrix cTM_;

    bool display_ = true;

    bool hrefFill_ = true;      // get fill attributes from reference
    bool hrefRender_ = true;    // get render attr (mask, filter, transform, opacity,
                                // clip path) from reference
    bool passStyle_ = true;     // pass style attributes to child node, TAGS
                                // circle/path/line/... = false
    bool inheritStyle_ = true;  // inherit style attributes from parent node, TAGS
                                // mask/defs/pattern/filter = false
    bool drawTraversed_ = true; // enable OnDraw, TAGS mask/defs/pattern/filter = false

    double canvasHeight_ = -1;

    double canvasWidth_ = -1;

    double canvasDiagonal_ = -1;

    /*
      N[1/Sqrt[2], 36]
      The inverse of the square root of 2.
      Provide enough digits for the 128-bit IEEE quad (36 significant digits).
  */
    const double M_SQRT1_2l = 0.707106781186547524400844362104849039;
};

} // namespace svg
} // namespace rnoh
