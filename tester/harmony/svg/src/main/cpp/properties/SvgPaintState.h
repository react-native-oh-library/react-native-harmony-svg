// from ArkUI "frameworks/core/components/common/properties/svg_paint_state.h"
#pragma once

// #include "base/memory/ace_type.h"
// #include "core/components/common/properties/animatable_double.h"
// #include "frameworks/core/components/common/layout/constants.h"
// #include "frameworks/core/components/common/properties/decoration.h"
// #include "frameworks/core/components/common/properties/paint_state.h"
// #include "frameworks/core/components/common/properties/text_style.h"
#include "properties/Color.h"
#include "properties/PaintState.h"
#include "properties/Decoration.h"

namespace rnoh {

const char ATTR_NAME_FILL[] = "fill";
const char ATTR_NAME_STROKE[] = "stroke";
const char ATTR_NAME_STROKE_WIDTH[] = "stroke-width";
const char ATTR_NAME_MITER_LIMIT[] = "stroke-miterlimit";
const char ATTR_NAME_STROKE_DASH_OFFSET[] = "stroke-dashoffset";
const char ATTR_NAME_FONT_SIZE[] = "font-size";
const char ATTR_NAME_FILL_OPACITY[] = "fill-opacity";
const char ATTR_NAME_STROKE_OPACITY[] = "stroke-opacity";
const char ATTR_NAME_LETTER_SPACING[] = "letter-spacing";
const char ANIMATOR_TYPE_MOTION[] = "motion";
const char ATTR_NAME_FILL_RULE_EVENODD[] = "evenodd";


class FillState {
public:
//     void SetContextAndCallback(const WeakPtr<PipelineContext> &context, const RenderNodeAnimationCallback &callback) {
//         color_.SetContextAndCallback(context, callback);
//         opacity_.SetContextAndCallback(context, callback);
//     }
//
    const Color &GetColor() const { return color_; }

    /**
     * set fill color
     * @param color
     * @param isSelf if false the color value inherited from the parent node, otherwise the value is setted by self
     */
    void SetColor(const Color &color, bool isSelf) {
        color_ = Color(color);
        hasColor_ = isSelf;
    }

    std::optional<Gradient> &GetGradient() { return gradient_; }

    const std::optional<Gradient> &GetGradient() const { return gradient_; }

    void SetGradient(const Gradient &gradient, bool isSelf) {
        gradient_ = std::make_optional(gradient);
        hasGradient_ = isSelf;
    }

    void SetOpacity(double opacity, bool isSelf) {
        opacity_ = opacity;
        hasOpacity_ = isSelf;
    }

    double GetOpacity() const { return opacity_; }

    void SetFillRule(const std::string &fillRule, bool isSelf) {
        fillRule_ = fillRule;
        hasFillRule_ = isSelf;
    }

    const std::string &GetFillRule() const { return fillRule_; }

//     bool IsEvenodd() const { return fillRule_ == ATTR_NAME_FILL_RULE_EVENODD; }
//
    void Inherit(const FillState &parent) {
        if (!hasColor_) {
            color_ = parent.GetColor();
        }
        if (!hasOpacity_) {
            opacity_ = parent.GetOpacity();
        }
        if (!hasFillRule_) {
            fillRule_ = parent.GetFillRule();
        }
        if (!hasGradient_) {
            gradient_ = parent.GetGradient();
        }
    }

    bool HasColor() const { return hasColor_; }

    bool HasOpacity() const { return hasOpacity_; }

    void SetHref(const std::string &href) { href_ = href; }

    const std::string &GetHref() const { return href_; }

protected:
    Color color_ = Color(Color::BLACK);
    double opacity_ = double(1.0);
    std::string fillRule_;
    std::optional<Gradient> gradient_;
    bool hasColor_ = false;
    bool hasOpacity_ = false;
    bool hasFillRule_ = false;
    bool hasGradient_ = false;
    std::string href_;
};

class StrokeState {
public:
//     void SetContextAndCallback(const WeakPtr<PipelineContext>& context, const RenderNodeAnimationCallback& callback)
//     {
//         lineWidth_.SetContextAndCallback(context, callback);
//         color_.SetContextAndCallback(context, callback);
//         opacity_.SetContextAndCallback(context, callback);
//         strokeDashOffset_.SetContextAndCallback(context, callback);
//     }
//
    const Color& GetColor() const
    {
        return color_;
    }

    void SetColor(const Color& color, bool isSelf)
    {
        color_ = color;
        hasColor_ = isSelf;
    }

    void SetOpacity(double opacity, bool isSelf)
    {
        opacity_ = opacity;
        hasOpacity_ = isSelf;
    }

    double GetOpacity() const
    {
        return opacity_;
    }

    LineCapStyle GetLineCap() const
    {
        return lineCap_;
    }

    void SetLineCap(LineCapStyle lineCap, bool isSelf)
    {
        lineCap_ = lineCap;
        hasLineCap_ = isSelf;
    }

    LineJoinStyle GetLineJoin() const
    {
        return lineJoin_;
    }

    void SetLineJoin(LineJoinStyle lineJoin, bool isSelf)
    {
        lineJoin_ = lineJoin;
        hasLineJoin_ = isSelf;
    }

    const double& GetLineWidth() const
    {
        return lineWidth_;
    }

    void SetLineWidth(double lineWidth, bool isSelf)
    {
        lineWidth_ = lineWidth;
        hasLineWidth_ = isSelf;
    }

    double GetMiterLimit() const
    {
        return miterLimit_;
    }

    void SetMiterLimit(double miterLimit, bool isSelf)
    {
        miterLimit_ = miterLimit;
        hasMiterLimit_ = isSelf;
    }

    const LineDashParam& GetLineDash() const
    {
        return lineDash_;
    }

    void SetLineDash(const LineDashParam& lineDash, bool isSelf)
    {
        lineDash_ = lineDash;
        hasLineDash_ = isSelf;
    }

    void SetLineDashOffset(double offset, bool isSelf)
    {
        lineDash_.dashOffset = offset;
        hasDashOffset_ = isSelf;
    }

    void SetLineDash(const std::vector<double>& segments, bool isSelf)
    {
        lineDash_.lineDash = segments;
        hasLineDash_ = isSelf;
    }

    void SetStrokeDashOffset(const double& offset, bool isSelf)
    {
        strokeDashOffset_ = offset;
        hasStrokeDashOffset_ = isSelf;
    }

    void SetStrokeDashArray(const std::vector<double>& segments, bool isSelf)
    {
        strokeDashArray_ = segments;
        hasStrokeDashArray_ = isSelf;
    }

    const double& GetStrokeDashOffset() const
    {
        return strokeDashOffset_;
    }

    const std::vector<double>& GetStrokeDashArray() const
    {
        return strokeDashArray_;
    }

    bool HasStroke() const
    {
        // The text outline is drawn only when stroke is set
        return color_ != Color::TRANSPARENT;
    }

    void Inherit(const StrokeState& strokeState)
    {
        if (!hasColor_) {
            color_ = strokeState.GetColor();
        }
        if (!hasOpacity_) {
            opacity_ = strokeState.GetOpacity();
        }
        if (!hasLineCap_) {
            lineCap_ = strokeState.GetLineCap();
        }
        if (!hasLineJoin_) {
            lineJoin_ = strokeState.GetLineJoin();
        }
        LOG(INFO) << "hasLineWIdth = " << hasLineWidth_ << " to inherit : " << strokeState.GetLineWidth();
        if (!hasLineWidth_) {
            lineWidth_ = strokeState.GetLineWidth();
        }
        if (!hasMiterLimit_) {
            miterLimit_ = strokeState.GetMiterLimit();
        }
        if (!hasLineDash_) {
            lineDash_.lineDash = strokeState.GetLineDash().lineDash;
        }
        if (!hasDashOffset_) {
            lineDash_.dashOffset = strokeState.GetLineDash().dashOffset;
        }
        if (!hasStrokeDashArray_) {
            strokeDashArray_ = strokeState.GetStrokeDashArray();
        }
        if (!hasStrokeDashOffset_) {
            strokeDashOffset_ = strokeState.GetStrokeDashOffset();
        }
    }

    bool HasColor() const
    {
        return hasColor_;
    }

    bool HasOpacity() const
    {
        return hasOpacity_;
    }

    bool HasLineWidth() const
    {
        return hasLineWidth_;
    }

    bool HasMiterLimit() const
    {
        return hasMiterLimit_;
    }

    bool HasDashOffset() const
    {
        return hasDashOffset_;
    }

    void SetHref(const std::string& href)
    {
        href_ = href;
    }

    const std::string& GetHref() const
    {
        return href_;
    }

private:
    Color color_ = Color::TRANSPARENT;
    double opacity_ = 1.0;
    LineCapStyle lineCap_ = LineCapStyle::BUTT;
    LineJoinStyle lineJoin_ = LineJoinStyle::MITER;
    double lineWidth_ = 1.0;
    double miterLimit_ = 4.0;
    LineDashParam lineDash_;
    std::vector<double> strokeDashArray_;
    double strokeDashOffset_;
    std::string href_;
    bool hasColor_ = false;
    bool hasOpacity_ = false;
    bool hasLineCap_ = false;
    bool hasLineJoin_ = false;
    bool hasLineWidth_ = false;
    bool hasMiterLimit_ = false;
    bool hasLineDash_ = false;
    bool hasDashOffset_ = false;
    bool hasStrokeDashArray_ = false;
    bool hasStrokeDashOffset_ = false;
};

class ClipState {
public:
    void SetClipRule(const std::string& clipRule, bool isSelf)
    {
        clipRule_ = clipRule;
        hasClipRule_ = isSelf;
    }

    const std::string& GetClipRule() const
    {
        return clipRule_;
    }

    bool IsEvenodd() const
    {
        return clipRule_ == ATTR_NAME_FILL_RULE_EVENODD;
    }

    void SetHref(const std::string& href, bool isSelf)
    {
        href_ = href;
        hasHref_ = isSelf;
    }

    const std::string& GetHref() const
    {
        return href_;
    }

    void Inherit(const ClipState& clipState)
    {
        if (!hasClipRule_) {
            clipRule_ = clipState.GetClipRule();
        }
        if (!hasHref_) {
            href_ = clipState.GetHref();
        }
    }

private:
    std::string clipRule_;
    std::string href_;
    bool hasClipRule_ = false;
    bool hasHref_ = false;
};

} // namespace rnoh
