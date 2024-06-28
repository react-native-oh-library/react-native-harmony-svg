#pragma once

#include <string>
#include "SvgGraphic.h"
#include <native_drawing/drawing_image.h>
#include <native_drawing/drawing_rect.h>
#include <native_drawing/drawing_pixel_map.h>
#include <native_drawing/drawing_sampling_options.h>


namespace rnoh {
namespace svg {

class SvgImage : public svg::SvgGraphic {
public:
    SvgImage() = default;
    ~SvgImage() override = default;
    
    void SetX(const std::string &x) { imageAttribute_.x = SvgAttributesParser::ParseDimension(x, true); }
    
    void SetY(const std::string &y) { imageAttribute_.y = SvgAttributesParser::ParseDimension(y, true); }
    
    void SetHeight(const std::string &height) { imageAttribute_.height = SvgAttributesParser::ParseDimension(height, true); }
    
    void SetWidth(const std::string &width) { imageAttribute_.width = SvgAttributesParser::ParseDimension(width, true); }
    
    void SetAlign(const std::string &align) { imageAttribute_.align = align; }
    
    void SetMeetOrSlice(const int &meetOrSlice) { imageAttribute_.meetOrSlice = meetOrSlice; }
    
    void SetImageSource(const facebook::react::ImageSource &src ) { imageAttribute_.src = src; }
    
    void setNativeResourceManager(const NativeResourceManager* mgr) { mgr_ = mgr; }
    
    void OnDraw(OH_Drawing_Canvas *canvas) override;

private:
    SvgImageAttribute imageAttribute_;
    const NativeResourceManager* mgr_;
};

} // namespace svg
} // namespace rnoh
