
#include "SvgSvg.h"
#include <string>
#include <vector>

#include "properties/Size.h"
#include "properties/SvgDomType.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"

#include <native_drawing/drawing_rect.h>
#include "utils/Utils.h"

namespace rnoh {
namespace {
const char DOM_SVG_SRC_VIEW_BOX[] = "viewBox";
}

SvgSvg::SvgSvg() : SvgGroup() {}

OH_Drawing_Path *SvgSvg::AsPath() const {
    auto *path = OH_Drawing_PathCreate();
    for (const auto &child : children_) {
        auto *childPath = child->AsPath();
        // path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}

Size SvgSvg::GetSize() const { return {attr_.width.Value(), attr_.height.Value()}; }

void SvgSvg::FitCanvas(OH_Drawing_Canvas *canvas) {
    float scaleViewBox = 1.0;
    float tx = 0.0;
    float ty = 0.0;
    constexpr float half = 0.5f;

    const Rect viewBox(attr_.x.Value(), attr_.y.Value(), attr_.vbWidth.Value(),
                       attr_.vbHeight.Value()); // should be viewBox attribute
    const auto svgSize = Size(attr_.width.Value(),
                              attr_.height.Value()); // should be width and height defined in attribute
    const auto layout = Size(OH_Drawing_CanvasGetWidth(canvas), OH_Drawing_CanvasGetHeight(canvas));
    LOG(INFO) << "[FitCanvas] viewBox = " << viewBox.ToString() << " svgSize = " << svgSize.ToString()
              << " layout = " << layout.ToString() << " canvas = " << canvas;
    /*
     * 1. viewBox_, svgSize_, and layout are on 3 different scales.
     * 2. Elements are painted in viewBox_ scale but displayed in layout scale.
     * 3. To center align svg content, we first align viewBox_ to svgSize_, then
     * we align svgSize_ to layout.
     * 4. Canvas is initially in layout scale, so transformation (tx, ty) needs to
     * be in that scale, too.
     */
    if (viewBox.IsValid()) {
        if (svgSize.IsValid() && !svgSize.IsInfinite()) {
            // center align viewBox_ to svg, need to map viewBox_ to the scale of
            // svgSize_
            scaleViewBox = std::min(svgSize.Width() / viewBox.Width(), svgSize.Height() / viewBox.Height());
            tx = svgSize.Width() * half - (viewBox.Width() * half + viewBox.Left()) * scaleViewBox;
            ty = svgSize.Height() * half - (viewBox.Height() * half + viewBox.Top()) * scaleViewBox;

            // center align svg to layout container
            tx += (layout.Width() - svgSize.Width()) * half;
            ty += (layout.Height() - svgSize.Height()) * half;
        } else if (!layout.IsEmpty()) {
            // no svgSize_, center align viewBox to layout container
            scaleViewBox = std::min(layout.Width() / viewBox.Width(), layout.Height() / viewBox.Height());
            tx = layout.Width() * half - (viewBox.Width() * half + viewBox.Left()) * scaleViewBox;
            ty = layout.Height() * half - (viewBox.Height() * half + viewBox.Top()) * scaleViewBox;
        } else {
            // LOGW("FitImage containerSize and svgSize is null");
        }
    }
    auto *rect = OH_Drawing_RectCreate(0.0f, 0.0f, layout.Width(), layout.Height());
    OH_Drawing_CanvasClipRect(canvas, rect, OH_Drawing_CanvasClipOp::INTERSECT, true);
    OH_Drawing_RectDestroy(rect);
    OH_Drawing_CanvasTranslate(canvas, tx, ty);

    if (NearZero(scaleViewBox)) {
        return;
    }
    OH_Drawing_CanvasScale(canvas, scaleViewBox, scaleViewBox);
    LOG(INFO) << "scale = " << scaleViewBox << " tx = " << tx << " ty = " << ty;
}

void SvgSvg::Draw(OH_Drawing_Canvas *canvas) {
    context_->SetViewBox(Rect(attr_.x.Value(), attr_.y.Value(), attr_.width.Value(), attr_.height.Value()));

    // apply scale
    OH_Drawing_CanvasSave(canvas);
    FitCanvas(canvas);
    SvgNode::Draw(canvas);
    OH_Drawing_CanvasRestore(canvas);
};
} // namespace rnoh
