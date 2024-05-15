#pragma once
#include "utils/StringUtils.h"
#include "utils/GlyphContext.h"
#include <native_drawing/drawing_text_typography.h>
#include <optional>
#include "properties/TextProperties.h"
#include "TextBase.h"
namespace rnoh {

class TextBase {
public:
    template <typename T>
    void UpdateTextProps(const std::shared_ptr<T> &props) {
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

        if (!props->verticalAlign.empty()) {
            auto align = props->verticalAlign;
            align.erase(0, align.find_first_not_of(" \t\r\n"));
            align.erase(align.find_last_not_of(" \t\r\n") + 1);
            size_t i = align.find_last_of(' ');
            align_ = alignmentBaselineFromStr(align.substr(i));
            baselineShift_ = align.substr(0, i);
        } else {
            align_ = AlignmentBaseline::baseline;
            baselineShift_.clear();
        }

        if (!props->baselineShift.empty()) {
            baselineShift_ = props->baselineShift;
        }
        if (!props->alignmentBaseline.empty()) {
            align_ = alignmentBaselineFromStr(props->alignmentBaseline);
        }

        lengthAdjust_ = textLengthAdjustFromStr(props->lengthAdjust);
    }

    void SetGlyphContext(const std::shared_ptr<GlyphContext> &ctx) { glyphCtx_ = ctx; }

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
    TextLengthAdjust lengthAdjust_ = TextLengthAdjust::spacing;
    AlignmentBaseline align_ = AlignmentBaseline::baseline;

    std::shared_ptr<GlyphContext> glyphCtx_;
};
} // namespace rnoh