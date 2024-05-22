#include "SvgSvg.h"
#include <string>
#include <vector>
#include <native_drawing/drawing_rect.h>
#include "properties/Size.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"
#include "utils/Utils.h"

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

Size SvgSvg::GetSize() const {
    return {width_, height_}; }

Rect SvgSvg::GetViewBox() const {
    return Rect(svgAttribute_.vbX.ConvertToPx(), svgAttribute_.vbY.ConvertToPx(), svgAttribute_.vbWidth.ConvertToPx(),
                svgAttribute_.vbHeight.ConvertToPx());
}

void SvgSvg::FitCanvas(OH_Drawing_Canvas *canvas) {
    // based on https://svgwg.org/svg2-draft/coords.html#ComputingAViewportsTransform

    // Let vb-x, vb-y, vb-width, vb-height be the min-x, min-y, width and height values of the
    // viewBox attribute respectively.
    float scaleX = 1.0;
    float scaleY = 1.0;
    float tx = 0.0;
    float ty = 0.0;
    constexpr float half = 0.5f;

    auto viewBox = GetViewBox(); // should be viewBox attribute
    const auto svgSize = GetSize();
    // TODO Since OH_Drawing API return px and RN pass vp
    const auto layout = svgSize;
    LOG(INFO) << "[FitCanvas] viewBox = " << viewBox.ToString() << " svgSize = " << svgSize.ToString()
              << " layout = " << layout.ToString() << " canvas = " << OH_Drawing_CanvasGetWidth(canvas) << ", "
              << OH_Drawing_CanvasGetHeight(canvas);

    if (viewBox.IsValid()) {
        if (svgSize.IsValid() && !svgSize.IsInfinite()) {
            // Initialize scale-x to e-width/vb-width.
            scaleX = svgSize.Width() / viewBox.Width();
            // Initialize scale-y to e-height/vb-height.
            scaleY = svgSize.Height() / viewBox.Height();

            // Initialize translate-x to e-x - (vb-x * scale-x).
            // Initialize translate-y to e-y - (vb-y * scale-y).
            tx = svgAttribute_.x.ConvertToPx()- (viewBox.Left() * scaleX);
            ty = svgAttribute_.y.ConvertToPx() - (viewBox.Top() * scaleY);

            // If align is 'none'
            if (svgAttribute_.meetOrSlice == MOS_NONE) {
                // Let scale be set the smaller value of scale-x and scale-y.
                // Assign scale-x and scale-y to scale.
                auto scale = scaleX = scaleY = std::min(scaleX, scaleY);
                // If scale is greater than 1
                if (scale > 1) {
                    // Minus translateX by (eWidth / scale - vbWidth) / 2
                    // Minus translateY by (eHeight / scale - vbHeight) / 2
                    tx -= (svgSize.Width() / scale - viewBox.Width()) * half;
                    ty -= (svgSize.Height() / scale - viewBox.Height()) * half;
                } else {
                    tx -= (svgSize.Width() - viewBox.Width() * scale) * half;
                    ty -= (svgSize.Height() - viewBox.Height() * scale) * half;
                }
            } else {
                // If align is not 'none' and meetOrSlice is 'meet', set the larger of scale-x and scale-y to
                // the smaller.
                // Otherwise, if align is not 'none' and meetOrSlice is 'slice', set the smaller of scale-x
                // and scale-y to the larger.
                if (svgAttribute_.align != "none" && svgAttribute_.meetOrSlice == MOS_MEET) {
                    scaleX = scaleY = std::min(scaleX, scaleY);
                } else if (svgAttribute_.align != "none" && svgAttribute_.meetOrSlice == MOS_SLICE) {
                    scaleX = scaleY = std::max(scaleX, scaleY);
                }

                // If align contains 'xMid', add (e-width - vb-width * scale-x) / 2 to translate-x.
                if (svgAttribute_.align.find("xMid") != std::string::npos) {
                    LOG(INFO) << "[FitCanvas] contain xMid: " << tx;
                    tx += (svgSize.Width() - viewBox.Width() * scaleX) * half;
                }

                // If align contains 'xMax', add (e-width - vb-width * scale-x) to translate-x.
                if (svgAttribute_.align.find("xMax") != std::string::npos) {
                    tx += (svgSize.Width() - viewBox.Width() * scaleX);
                }

                // If align contains 'yMid', add (e-height - vb-height * scale-y) / 2 to translate-y.
                if (svgAttribute_.align.find("YMid") != std::string::npos) {
                    LOG(INFO) << "[FitCanvas] contain YMid: " << ty;
                    ty += (svgSize.Height() - viewBox.Height() * scaleY) * half;
                }

                // If align contains 'yMax', add (e-height - vb-height * scale-y) to translate-y.
                if (svgAttribute_.align.find("YMax") != std::string::npos) {
                    //                     translateY += (eHeight - vbHeight * scaleY);
                    ty += (svgSize.Height() - viewBox.Height() * scaleY);
                }
            }
        }
    }
    drawing::Rect rect(0.0f, 0.0f, layout.Width(), layout.Height());
    OH_Drawing_CanvasClipRect(canvas, rect.get(), OH_Drawing_CanvasClipOp::INTERSECT, true);
    // The transform applied to content contained by the element is given by
    // translate(translate-x, translate-y) scale(scale-x, scale-y).
    OH_Drawing_CanvasTranslate(canvas, tx, ty);
    if (NearZero(scaleX) || NearZero(scaleY)) {
        return;
    }
    OH_Drawing_CanvasScale(canvas, scaleX, scaleY);
    LOG(INFO) << "[FitCanvas] scale = " << scaleX << ", " << scaleY << " tx = " << tx << " ty = " << ty;
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
    FitCanvas(canvas);
    SvgNode::Draw(canvas);
    OH_Drawing_CanvasRestore(canvas);
};

} // namespace svg
} // namespace rnoh
