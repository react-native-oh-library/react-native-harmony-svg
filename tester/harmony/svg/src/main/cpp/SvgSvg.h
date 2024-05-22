#pragma once

#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_path.h>
#include "SvgGroup.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgSvg : public SvgGroup {
public:
    SvgSvg();
    ~SvgSvg() override = default;

    drawing::Path AsPath() override;

    Size GetSize() const;
    
    Rect GetViewBox() const;
    
    void Draw(OH_Drawing_Canvas *canvas) override;

    void SetVbX(const double &vbX) { svgAttribute_.vbX = Dimension(vbX, DimensionUnit::VP); }
    void SetVbY(const double &vbY) { svgAttribute_.vbY = Dimension(vbY, DimensionUnit::VP); }
    void SetVbWidth(const double &vbWidth) { svgAttribute_.vbWidth = Dimension(vbWidth, DimensionUnit::VP); }
    void SetVbHeight(const double &vbHeight) { svgAttribute_.vbHeight = Dimension(vbHeight, DimensionUnit::VP); }
    void SetX(const double &x) { svgAttribute_.x = Dimension(x, DimensionUnit::VP); }
    void SetY(const double &y) { svgAttribute_.y = Dimension(y, DimensionUnit::VP); }
    void SetWidth(const std::string &width) { svgAttribute_.width = SvgAttributesParser::ParseDimension(width, true); }
    void SetHeight(const std::string &height) { svgAttribute_.height = SvgAttributesParser::ParseDimension(height, true); }
    void SetAlign(const std::string &align) { svgAttribute_.align = align; }
    void SetMeetOrSlice(const int &meetOrSlice) { svgAttribute_.meetOrSlice = meetOrSlice; }

private:
    SvgAttribute svgAttribute_;
    
    float width_ = 0;
    
    float height_ = 0;
    
    void FitCanvas(OH_Drawing_Canvas *canvas);
};

} // namespace svg
} // namespace rnoh
