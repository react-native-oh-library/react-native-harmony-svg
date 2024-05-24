#include "SvgSvg.h"
#include <string>
#include <vector>
#include <native_drawing/drawing_rect.h>
#include "properties/Size.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"
#include "utils/Utils.h"
#include "properties/ViewBox.h"

namespace rnoh {
namespace svg {

namespace {
const int MOS_MEET = 0;
const int MOS_SLICE = 1;
const int MOS_NONE = 2;
} // namespace

SvgSvg::SvgSvg() : SvgGroup() {}

drawing::Path SvgSvg::AsPath() {
    drawing::Path path;
    for (const auto &child : children_) {
        auto childPath = child->AsPath();
        path.Union(childPath);
    }
    return path;
}

Size SvgSvg::GetSize() const { return {width_, height_}; }

Rect SvgSvg::GetViewBox() const {
    return Rect(svgAttribute_.vbX.ConvertToPx(scale_), svgAttribute_.vbY.ConvertToPx(scale_), svgAttribute_.vbWidth.ConvertToPx(scale_),
                svgAttribute_.vbHeight.ConvertToPx(scale_));
}

drawing::Matrix SvgSvg::FitCanvas(OH_Drawing_Canvas *canvas) {
    const auto svgSize = GetSize();
    // TODO Since OH_Drawing API return px and RN pass vp
    const auto vbRect = GetViewBox(); // should be viewBox attribute
    const auto eRect = Rect(svgAttribute_.x.ConvertToPx(scale_), svgAttribute_.y.ConvertToPx(scale_), svgSize.Width(), svgSize.Height());
    LOG(INFO) << "[FitCanvas] viewBox = " << vbRect.ToString() << " svgSize = " << svgSize.ToString() << " canvas = " << OH_Drawing_CanvasGetWidth(canvas) << ", "
              << OH_Drawing_CanvasGetHeight(canvas);
    drawing::Rect clipRect(0.0f, 0.0f, svgSize.Width(), svgSize.Height());
    OH_Drawing_CanvasClipRect(canvas, clipRect.get(), OH_Drawing_CanvasClipOp::INTERSECT, true);
    drawing::Matrix transformMatrix;
    if (vbRect.IsValid()) {
        transformMatrix = ViewBox::getTransform(vbRect, eRect, svgAttribute_.align, svgAttribute_.meetOrSlice);
        OH_Drawing_CanvasConcatMatrix(canvas, transformMatrix.get());
    }
    return transformMatrix;
}

void SvgSvg::Draw(OH_Drawing_Canvas *canvas) {
    float width = OH_Drawing_CanvasGetWidth(canvas);
    float height = OH_Drawing_CanvasGetHeight(canvas);
    context_->SetCanvasBounds(Rect(0.0f, 0.0f, width, height));
    context_->SetRootViewBox(GetViewBox());

    //     width_ = relativeOnWidth(svgAttribute_.width);
    //     height_ = relativeOnHeight(svgAttribute_.height);
    width_ = width;
    height_ = height;
    LOG(INFO) << "[svgView] bbHeight: " << svgAttribute_.height.Value();
    LOG(INFO) << "[svgView] bbWidth: " << svgAttribute_.height.Value();
    LOG(INFO) << "[svgView] svg Height: " << height_;
    LOG(INFO) << "[svgView] svg Width: " << width_;
    LOG(INFO) << "[svgView] canvas Height: " << height;
    LOG(INFO) << "[svgView] canvas Width: " << width;
    context_->SetSvgSize(Size(width_, height_));
    // apply scale
    OH_Drawing_CanvasSave(canvas);
    auto canvasTransformMatrix = FitCanvas(canvas);
    context_->SetCanvasScale(canvasTransformMatrix.GetValue(0), canvasTransformMatrix.GetValue(4));
    SvgNode::Draw(canvas);
    OH_Drawing_CanvasRestore(canvas);
};

} // namespace svg
} // namespace rnoh
