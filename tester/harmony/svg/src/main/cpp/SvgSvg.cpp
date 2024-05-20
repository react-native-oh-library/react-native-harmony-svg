#include "SvgSvg.h"
#include <string>
#include <vector>

#include "properties/Size.h"
#include "properties/SvgDomType.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"

#include <native_drawing/drawing_rect.h>
#include "utils/Utils.h"
#include "properties/ViewBox.h"

namespace rnoh {
namespace svg {

SvgSvg::SvgSvg() : SvgGroup() {}

drawing::Path SvgSvg::AsPath() {
    drawing::Path path;
    for (const auto &child : children_) {
        auto childPath = child->AsPath();
        path.Union(childPath);
    }
    return path;
}

Size SvgSvg::GetSize() const { return {attr_.width.Value(), attr_.height.Value()}; }

Rect SvgSvg::GetViewBox() const {
    return Rect(vpToPx(attr_.vbX.Value()), vpToPx(attr_.vbY.Value()), vpToPx(attr_.vbWidth.Value()),
                vpToPx(attr_.vbHeight.Value()));
}

void SvgSvg::FitCanvas(OH_Drawing_Canvas *canvas) {
    auto vbRect = GetViewBox(); // should be viewBox attribute
    const auto eRect =
        Rect(attr_.x.Value(), attr_.y.Value(), OH_Drawing_CanvasGetWidth(canvas), OH_Drawing_CanvasGetHeight(canvas));
    drawing::Rect rect(0.0f, 0.0f, eRect.Width(), eRect.Height());
    OH_Drawing_CanvasClipRect(canvas, rect.get(), OH_Drawing_CanvasClipOp::INTERSECT, true);
    drawing::Matrix transformMatrix;
    transformMatrix = ViewBox::getTransform(vbRect, eRect, attr_.align, attr_.meetOrSlice);
    OH_Drawing_CanvasConcatMatrix(canvas, transformMatrix.get());
}

void SvgSvg::Draw(OH_Drawing_Canvas *canvas) {
    context_->SetRootViewBox(GetViewBox());
    context_->SetSvgSize(Size(OH_Drawing_CanvasGetWidth(canvas), OH_Drawing_CanvasGetHeight(canvas)));
    // apply scale
    OH_Drawing_CanvasSave(canvas);
    FitCanvas(canvas);
    SvgNode::Draw(canvas);
    OH_Drawing_CanvasRestore(canvas);
};

} // namespace svg
} // namespace rnoh
