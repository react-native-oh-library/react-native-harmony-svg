#pragma once

#include "SvgGroup.h"
#include "utils/StringUtils.h"
#include "utils/GlyphContext.h"
#include <native_drawing/drawing_text_typography.h>

namespace rnoh {

class SvgText : public SvgGroup {
public:
    SvgText() = default;
    ~SvgText() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    template<typename T>
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
    }

    double fontSize;

protected:
    std::vector<Dimension> x_;
    std::vector<Dimension> y_;
    std::vector<Dimension> dx_;
    std::vector<Dimension> dy_;
    std::vector<Dimension> rotate_;

    std::shared_ptr<GlyphContext> glyphCtx_;
};

} // namespace rnoh