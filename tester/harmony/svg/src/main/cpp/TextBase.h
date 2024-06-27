#pragma once
#include "utils/StringUtils.h"
#include "utils/GlyphContext.h"
#include "properties/TextProperties.h"
#include <native_drawing/drawing_text_typography.h>
#include <optional>

namespace rnoh {
namespace svg {

class TextBase {
public:
    template <typename T> void UpdateTextProps(const std::shared_ptr<T> &props) {
        x_.clear();
        for (auto const &value : props->x) {
            x_.push_back(StringUtils::FromString(value));
        }
        y_.clear();
        for (auto const &value : props->y) {
            y_.push_back(StringUtils::FromString(value));
        }
        dx_.clear();
        for (auto const &value : props->dx) {
            dx_.push_back(StringUtils::FromString(value));
        }
        dy_.clear();
        for (auto const &value : props->dy) {
            dy_.push_back(StringUtils::FromString(value));
        }
        rotate_.clear();
        for (auto const &value : props->rotate) {
            rotate_.push_back(StringUtils::FromString(value));
        }
        if (props->inlineSize.empty()) {
            inlineSize_.reset();
        } else {
            inlineSize_ = StringUtils::FromString(props->inlineSize);
        }

        if (props->textLength.empty()) {
            textLength_.reset();
        } else {
            textLength_ = StringUtils::FromString(props->textLength);
        }

        hasBaselineShift_ = false;
        hasAlign_ = false;
        if (!props->verticalAlign.empty()) {
            auto align = props->verticalAlign;
            align.erase(0, align.find_first_not_of(" \t\r\n"));
            align.erase(align.find_last_not_of(" \t\r\n") + 1);
            size_t i = align.find_last_of(' ');
            align_ = alignmentBaselineFromStr(align.substr(i));
            baselineShift_ = align.substr(0, i);
            hasAlign_ = true;
            hasBaselineShift_ = true;
        } else {
            align_ = AlignmentBaseline::baseline;
            baselineShift_.clear();
            hasAlign_ = false;
            hasBaselineShift_ = false;
        }

        if (!props->baselineShift.empty()) {
            baselineShift_ = props->baselineShift;
            hasBaselineShift_ = true;
        }
        if (!props->alignmentBaseline.empty()) {
            align_ = alignmentBaselineFromStr(props->alignmentBaseline);
            hasAlign_ = true;
        }

        lengthAdjust_ = textLengthAdjustFromStr(props->lengthAdjust);
    }

    void SetGlyphContext(const std::shared_ptr<GlyphContext> &ctx) { glyphCtx_ = ctx; }
    
    void setAlignmentBaseline(const AlignmentBaseline &alignmentBaseline) { align_ = alignmentBaseline; }
    
    bool hasAlignmentBaseline() { return hasAlign_; }
    
    void setBaselineShift(const std::string &baselineShift) { baselineShift_ = baselineShift; }
    
    bool hasBaselineShift() { return hasBaselineShift_; }

protected:
    void InitGlyph(OH_Drawing_Canvas *canvas, double scale);

    std::vector<Dimension> x_;
    std::vector<Dimension> y_;
    std::vector<Dimension> dx_;
    std::vector<Dimension> dy_;
    std::vector<Dimension> rotate_;
    std::optional<Dimension> inlineSize_;
    std::optional<Dimension> textLength_;

    std::string baselineShift_;
    bool hasBaselineShift_ = false;
    TextLengthAdjust lengthAdjust_ = TextLengthAdjust::spacing;
    AlignmentBaseline align_ = AlignmentBaseline::baseline;
    bool hasAlign_ = false;

    std::shared_ptr<GlyphContext> glyphCtx_;
};

} // namespace svg
} // namespace rnoh