// from ArkUI "frameworks/core/components_ng/svg/parse/svg_graphic.h"

#pragma once

#include "SvgNode.h"
#include "RNOH/CppComponentInstance.h"
#include "utils/StringUtils.h"
#include "utils/SvgMarkerPositionUtils.h"
#include "drawing/Brush.h"
#include "drawing/Path.h"
#include "drawing/Pen.h"
#include <native_drawing/drawing_brush.h>
#include <native_drawing/drawing_path_effect.h>
#include <native_drawing/drawing_pen.h>


namespace rnoh {
namespace svg {

class SvgGraphic : virtual public SvgNode {
public:
     SvgGraphic() : SvgNode() {}
    ~SvgGraphic() noexcept override = default; 


    void OnDraw(OH_Drawing_Canvas *canvas) override;
protected:
    drawing::Path path_ {};
    drawing::Brush fillBrush_ {};
    drawing::Pen strokePen_ {};

    // Use Brush to draw fill
    void OnGraphicFill(OH_Drawing_Canvas *canvas);
    // Use Pen to draw stroke
    void OnGraphicStroke(OH_Drawing_Canvas *canvas);

    bool UpdateFillStyle(bool antiAlias = true);
    bool UpdateStrokeStyle(bool antiAlias = true);
    void UpdateGradient(std::optional<Gradient> &gradient);
    void SetFillGradientStyle(double opacity);
    void SetStrokeGradientStyle(double opacity);
    bool SetPatternStyle();
    void UpdateLineDash();

    std::vector<PathElement> elements_;

private:
    void DrawMarker(OH_Drawing_Canvas *canvas);
    // TODO void UpdateColorFilter(OH_Drawing_Filter *filter);
};

} // namespace svg
} // namespace rnoh