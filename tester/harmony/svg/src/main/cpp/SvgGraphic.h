// from ArkUI "frameworks/core/components_ng/svg/parse/svg_graphic.h"

#pragma once
#include <native_drawing/drawing_brush.h>
#include <native_drawing/drawing_path_effect.h>
#include <native_drawing/drawing_pen.h>
#include "SvgNode.h"
#include "RNOH/CppComponentInstance.h"
#include "utils/StringUtils.h"
#include "utils/SvgMarkerPositionUtils.h"

namespace rnoh {
namespace svg {

class SvgGraphic : virtual public SvgNode {
public:
    SvgGraphic() : SvgNode() {
        fillBrush_ = OH_Drawing_BrushCreate();
        strokePen_ = OH_Drawing_PenCreate();
        path_ = OH_Drawing_PathCreate();
    }
    //     virtual ~SvgGraphic() override = default;
    ~SvgGraphic() override {
        OH_Drawing_BrushDestroy(fillBrush_);
        OH_Drawing_PenDestroy(strokePen_);
        OH_Drawing_PathDestroy(path_);
        OH_Drawing_PathEffectDestroy(dashPathEffect_);
    }


    void OnDraw(OH_Drawing_Canvas *canvas) override;
protected:
    OH_Drawing_Path *path_;
    OH_Drawing_Brush *fillBrush_;
    OH_Drawing_Pen *strokePen_;
    OH_Drawing_PathEffect *dashPathEffect_;

    // Use Brush to draw fill
    void OnGraphicFill(OH_Drawing_Canvas *canvas);
    // Use Pen to draw stroke
    void OnGraphicStroke(OH_Drawing_Canvas *canvas);

    bool UpdateFillStyle(bool antiAlias = true);
    bool UpdateStrokeStyle(bool antiAlias = true);
    void UpdateGradient();
    void SetGradientStyle(double opacity);
    void SetPatternStyle();
    void UpdateLineDash();

    std::vector<PathElement> elements_;

private:
    void DrawMarker(OH_Drawing_Canvas *canvas);
    // TODO void UpdateColorFilter(OH_Drawing_Filter *filter);
};

} // namespace svg
} // namespace rnoh