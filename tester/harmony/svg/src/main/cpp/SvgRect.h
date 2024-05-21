#pragma once

#include "SvgGraphic.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgRect : public SvgGraphic {
public:
    using Float = facebook::react::Float;
    SvgRect() = default;
    ~SvgRect() override = default;

    void SetX(const std::string &x) { rectAttribute_.x = SvgAttributesParser::ParseDimension(x, true); }
    void SetY(const std::string &y) { rectAttribute_.y = SvgAttributesParser::ParseDimension(y, true); }
    void SetRX(const std::string &rx) { rectAttribute_.rx = SvgAttributesParser::ParseDimension(rx, true); }
    void SetRY(const std::string &ry) { rectAttribute_.ry = SvgAttributesParser::ParseDimension(ry, true); }
    void SetWidth(const std::string &width) { rectAttribute_.width = SvgAttributesParser::ParseDimension(width, true); }
    void SetHeight(const std::string &height) { rectAttribute_.height = SvgAttributesParser::ParseDimension(height, true); }
    drawing::Path AsPath() override;
private:
    SvgRectAttribute rectAttribute_;
};

} // namespace svg
} // namespace rnoh