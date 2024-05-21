#pragma once

#include "SvgGraphic.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgLine : public SvgGraphic {
public:
    using Float = facebook::react::Float;
    SvgLine() = default;
    ~SvgLine() override = default;

    drawing::Path AsPath() override;
    void SetX1(const std::string &x1) { lineAttribute_.x1 = SvgAttributesParser::ParseDimension(x1, true); }
    void SetY1(const std::string &y1) { lineAttribute_.y1 = SvgAttributesParser::ParseDimension(y1, true); }
    void SetX2(const std::string &x2) { lineAttribute_.x2 = SvgAttributesParser::ParseDimension(x2, true); }
    void SetY2(const std::string &y2) { lineAttribute_.y2 = SvgAttributesParser::ParseDimension(y2, true); }

private:
    SvgLineAttribute lineAttribute_;
};

} // namespace svg
} // namespace rnoh