/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SvgGraphic.h"
#include <native_drawing/drawing_bitmap.h>
#include <native_drawing/drawing_filter.h>
#include <native_drawing/drawing_image.h>
#include <native_drawing/drawing_mask_filter.h>
#include <native_drawing/drawing_path_effect.h>
#include <native_drawing/drawing_sampling_options.h>
#include <native_drawing/drawing_shader_effect.h>
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_types.h>
#include "utils/SvgMarkerPositionUtils.h"
#include "SvgMarker.h"
#include "properties/ViewBox.h"
#include "drawing/Rect.h"

namespace rnoh {
namespace svg {

void SvgGraphic::OnDraw(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[SVGGraphic] onDraw marker = " << attributes_.markerStart << " " << attributes_.markerMid << " "
              << attributes_.markerEnd;
    //     OH_Drawing_BrushReset(fillBrush_.get());
    //     OH_Drawing_PenReset(strokePen_.get());
    // 获取子类的绘制路径。
    path_ = AsPath();
    if (attributes_.strokeState.GetVectorEffect()) {}
    UpdateGradient();
    if (UpdateFillStyle()) {
        OnGraphicFill(canvas);
    }
    //     OnGraphicFill(canvas);
    UpdateStrokeStyle();
    OnGraphicStroke(canvas);
    if (!attributes_.markerStart.empty() || !attributes_.markerMid.empty() || !attributes_.markerEnd.empty()) {
        LOG(INFO) << "DRaw marker";
        DrawMarker(canvas);
    }
}
void SvgGraphic::OnGraphicFill(OH_Drawing_Canvas *canvas) {
    auto smoothEdge = GetSmoothEdge();
    if (GreatNotEqual(smoothEdge, 0.0f)) {
        LOG(INFO) << "[svg] OnGraphicFill1";
        auto *filter = OH_Drawing_FilterCreate();
        auto *maskFilter =
            OH_Drawing_MaskFilterCreateBlur(OH_Drawing_BlurType::NORMAL, static_cast<double>(smoothEdge), false);
        OH_Drawing_FilterSetMaskFilter(filter, maskFilter);

        /* copy constructor missing */
        auto tmpFillBrush = fillBrush_;
        OH_Drawing_BrushSetFilter(tmpFillBrush.get(), filter);
        OH_Drawing_CanvasAttachBrush(canvas, tmpFillBrush.get());
        OH_Drawing_CanvasDrawPath(canvas, path_.get());
        OH_Drawing_CanvasDetachBrush(canvas);

        OH_Drawing_FilterDestroy(filter);
        OH_Drawing_MaskFilterDestroy(maskFilter);
    } else {
        LOG(INFO) << "[svg] OnGraphicFill2";
        OH_Drawing_CanvasAttachBrush(canvas, fillBrush_.get());
        OH_Drawing_CanvasDrawPath(canvas, path_.get());
        OH_Drawing_CanvasDetachBrush(canvas);
    }
}

// Use Pen to draw stroke
void SvgGraphic::OnGraphicStroke(OH_Drawing_Canvas *canvas) {
    auto smoothEdge = GetSmoothEdge();
    if (GreatNotEqual(smoothEdge, 0.0f)) {
        LOG(INFO) << "[svg] OnGraphicStroke1";
        auto *filter = OH_Drawing_FilterCreate();
        auto *maskFilter =
            OH_Drawing_MaskFilterCreateBlur(OH_Drawing_BlurType::NORMAL, static_cast<double>(smoothEdge), false);
        OH_Drawing_FilterSetMaskFilter(filter, maskFilter);

        /* copy constructor missing */
        auto tmpStrokePen = strokePen_;
        OH_Drawing_PenSetFilter(tmpStrokePen.get(), filter);
        OH_Drawing_CanvasAttachPen(canvas, tmpStrokePen.get());
        OH_Drawing_CanvasDrawPath(canvas, path_.get());
        OH_Drawing_CanvasDetachPen(canvas);

        OH_Drawing_FilterDestroy(filter);
        OH_Drawing_MaskFilterDestroy(maskFilter);
    } else {
        LOG(INFO) << "[svg] OnGraphicStroke2";
        OH_Drawing_CanvasAttachPen(canvas, strokePen_.get());
        OH_Drawing_CanvasDrawPath(canvas, path_.get());
        OH_Drawing_CanvasDetachPen(canvas);
    }
}

// todo implement bounds
void SvgGraphic::UpdateGradient() {
    auto &fillState_ = attributes_.fillState;
    auto &gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    // objectBoundingBox - 0(DEFAULT), userSpaceOnUse - 1
    auto nodeBounds = (gradient->GetGradientUnits() == Unit::objectBoundingBox)
                          ? AsBounds()
                          : Rect(0, 0, context_->GetSvgSize().Width(), context_->GetSvgSize().Height());
    if (gradient->GetType() == GradientType::LINEAR) {
        const auto &linearGradient = gradient->GetLinearGradient();
        auto gradientInfo = LinearGradientInfo();
        if (linearGradient.x1.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.x1 = nodeBounds.Left() + linearGradient.x1->ConvertToPx(nodeBounds.Width());
        } else {
            gradientInfo.x1 = linearGradient.x1->ConvertToPx(nodeBounds.Width());
        }
        if (linearGradient.y1.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.y1 = nodeBounds.Top() + linearGradient.y1->ConvertToPx(nodeBounds.Height());
        } else {
            gradientInfo.y1 = linearGradient.y1->ConvertToPx(nodeBounds.Height());
        }
        if (linearGradient.x2.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.x2 = nodeBounds.Left() + linearGradient.x2->ConvertToPx(nodeBounds.Width());
        } else {
            gradientInfo.x2 = linearGradient.x2->ConvertToPx(nodeBounds.Width());
        }
        if (linearGradient.y2.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.y2 = nodeBounds.Top() + linearGradient.y2->ConvertToPx(nodeBounds.Height());
        } else {
            gradientInfo.y2 = linearGradient.y2->ConvertToPx(nodeBounds.Height());
        }
        gradient->SetLinearGradientInfo(gradientInfo);
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        const auto &radialGradient = gradient->GetRadialGradient();
        auto gradientInfo = RadialGradientInfo();
        if (radialGradient.radialCenterX.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.cx = nodeBounds.Left() + radialGradient.radialCenterX->ConvertToPx(nodeBounds.Width());
        } else {
            gradientInfo.cx = radialGradient.radialCenterX->ConvertToPx(nodeBounds.Width());
        }
        if (radialGradient.radialCenterY.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.cy = nodeBounds.Top() + radialGradient.radialCenterY->ConvertToPx(nodeBounds.Height());
        } else {
            gradientInfo.cy = radialGradient.radialCenterY->ConvertToPx(nodeBounds.Height());
        }
        if (radialGradient.fRadialCenterX.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.fx = nodeBounds.Left() + radialGradient.fRadialCenterX->ConvertToPx(nodeBounds.Width());
        } else {
            gradientInfo.fx = radialGradient.fRadialCenterX->ConvertToPx(nodeBounds.Width());
        }
        if (radialGradient.fRadialCenterY.value().Unit() == DimensionUnit::PERCENT) {
            gradientInfo.fy = nodeBounds.Top() + radialGradient.fRadialCenterY->ConvertToPx(nodeBounds.Height());
        } else {
            gradientInfo.fy = radialGradient.fRadialCenterY->ConvertToPx(nodeBounds.Height());
        }
        gradientInfo.rx = radialGradient.radialHorizontalSize->ConvertToPx(nodeBounds.Width());
        gradientInfo.ry = radialGradient.radialVerticalSize->ConvertToPx(nodeBounds.Height());
        gradient->SetRadialGradientInfo(gradientInfo);
    }
}
bool SvgGraphic::UpdateFillStyle(bool antiAlias) {
    const auto &fillState_ = attributes_.fillState;
    if (fillState_.GetColor() == Color::TRANSPARENT && !fillState_.GetGradient() && !fillState_.GetPatternAttr()) {
        return false;
    }
    double curOpacity = fillState_.GetOpacity() * attributes_.opacity;
    fillBrush_.SetAntiAlias(antiAlias);
    if (fillState_.GetGradient()) {
        LOG(INFO) << "[SVGGraphic] SetGradientStyle";
        SetGradientStyle(curOpacity);
    } else if (fillState_.GetPatternAttr()) {
        LOG(INFO) << "[SVGGraphic] SetPatternStyle";
        SetPatternStyle();
    } else {
        fillBrush_.SetColor(fillState_.GetColor().BlendOpacity(curOpacity).GetValue());
        path_.SetFillType(fillState_.GetFillRuleForDraw());
    }
    return true;
}
void SvgGraphic::SetGradientStyle(double opacity) {
    const auto &fillState_ = attributes_.fillState;
    auto gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return;
    }
    std::vector<float> pos;
    std::vector<uint32_t> colors;
    for (const auto &gradientColor : gradientColors) {
        pos.push_back(static_cast<float>(gradientColor.GetDimension().Value()));
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    OH_Drawing_Matrix *transMatrix = OH_Drawing_MatrixCreate();
    if (gradient->GetGradientTransform().size() == 9) {
        OH_Drawing_MatrixSetMatrix(transMatrix, gradient->GetGradientTransform()[0],
                                   gradient->GetGradientTransform()[1], gradient->GetGradientTransform()[2],
                                   gradient->GetGradientTransform()[3], gradient->GetGradientTransform()[4],
                                   gradient->GetGradientTransform()[5], gradient->GetGradientTransform()[6],
                                   gradient->GetGradientTransform()[7], gradient->GetGradientTransform()[8]);
    }
    if (gradient->GetType() == GradientType::LINEAR && gradient->IsValid()) {
        auto info = gradient->GetLinearGradientInfo();
        OH_Drawing_Point2D ptsPoint2D[2] = {
            {static_cast<float>(info.x1), static_cast<float>(info.y1)},
            {static_cast<float>(info.x2), static_cast<float>(info.y2)},
        };
        OH_Drawing_BrushSetShaderEffect(
            fillBrush_.get(), OH_Drawing_ShaderEffectCreateLinearGradientWithLocalMatrix(
                            &ptsPoint2D[0], &ptsPoint2D[1], colors.data(), pos.data(), colors.size(),
                            static_cast<OH_Drawing_TileMode>(gradient->GetSpreadMethod()), transMatrix));
    }
    if (gradient->GetType() == GradientType::RADIAL && gradient->IsValid()) {
        auto info = gradient->GetRadialGradientInfo();
        OH_Drawing_Matrix *scaleMatrix = info.ry < info.rx
                                             ? OH_Drawing_MatrixCreateScale(1, info.ry / info.rx, info.cx, info.cy)
                                             : OH_Drawing_MatrixCreateScale(info.rx / info.ry, 1, info.cx, info.cy);
        OH_Drawing_Point2D focal = {static_cast<float>(info.fx), static_cast<float>(info.fy)};
        OH_Drawing_Point2D center = {static_cast<float>(info.cx), static_cast<float>(info.cy)};
        OH_Drawing_Matrix *concatMatrix = OH_Drawing_MatrixCreate();
        OH_Drawing_MatrixConcat(concatMatrix, scaleMatrix, transMatrix);
//         OH_Drawing_BrushSetShaderEffect(fillBrush_.get(), OH_Drawing_ShaderEffectCreateTwoPointConicalGradient(
//                                                         &focal, 0, &center, info.rx > info.ry ? info.rx : info.ry,
//                                                         colors.data(), pos.data(), colors.size(),
//                                                         static_cast<OH_Drawing_TileMode>(gradient->GetSpreadMethod()),
//                                                         concatMatrix));
        OH_Drawing_MatrixDestroy(concatMatrix);
        OH_Drawing_MatrixDestroy(scaleMatrix);
    }
    OH_Drawing_MatrixDestroy(transMatrix);
}

void SvgGraphic::SetPatternStyle() {
    LOG(INFO) << "[SVGGraphic pattern] SetPatternStyle";
    const auto &fillState_ = attributes_.fillState;
    auto pattern = fillState_.GetPatternAttr();
    CHECK_NULL_VOID(pattern);
    Unit patternUnits = pattern->getPatternUnits();
    Unit patternContentUnits = pattern->getPatternContentUnits();

    OH_Drawing_Canvas *canvas = OH_Drawing_CanvasCreate();

    Dimension x_ = pattern->getX();
    Dimension y_ = pattern->getY();
    Dimension width_ = pattern->getWidth();
    Dimension height_ = pattern->getHeight();
    float mMinX = pattern->getmMinX();
    float mMinY = pattern->getmMinY();
    float mVbWidth = pattern->getmVbWidth();
    float mVbHeight = pattern->getmVbHeight();
    std::string mAlign = pattern->getmAlign();
    int mMeetOrSlice = pattern->getmMeetOrSlice();

    Rect nodeBounds;
    float left = 0;
    float top = 0;
    float width;
    float height;
    if (patternUnits == Unit::objectBoundingBox) {
        nodeBounds = AsBounds();
        left =nodeBounds.Left();
        top = nodeBounds.Top();
    } else {
        nodeBounds = GetRootViewBox();
    }
    
    width = nodeBounds.Width();
    height = nodeBounds.Height();


    drawing::Rect Bounds_(left, top, width + left, height + top);

    float offsetwidth = Bounds_.GetWidth();
    float offsetheight = Bounds_.GetHeight();

    bool isObjectBox = patternUnits == Unit::objectBoundingBox;
    double x = x_.FromRelative(isObjectBox, offsetwidth, scale_);
    double y = y_.FromRelative(isObjectBox, offsetheight, scale_);
    double w = width_.FromRelative(isObjectBox, offsetwidth, scale_);
    double h = height_.FromRelative(isObjectBox, offsetheight, scale_);
    if (!(w > 1 && h > 1)) {
        return;
    }

    OH_Drawing_Bitmap *bitmap = OH_Drawing_BitmapCreate();
    OH_Drawing_BitmapFormat format = {COLOR_FORMAT_RGBA_8888, ALPHA_FORMAT_OPAQUE};

    OH_Drawing_BitmapBuild(bitmap, int(w), int(h), &format);
    OH_Drawing_CanvasBind(canvas, bitmap);

    // set background color to white
    drawing::Brush brush;
    brush.SetColor(0xffffffff);
    OH_Drawing_CanvasDrawBackground(canvas, brush.get());

    Rect vbRect(mMinX * scale_, mMinY * scale_, (mMinX + mVbWidth) * scale_, (mMinY + mVbHeight) * scale_);
    Rect eRect = Rect(x, y, w, h);
    if (vbRect.IsValid()) {
        OH_Drawing_Matrix *viewBoxMatrix = ViewBox::getTransform(vbRect, eRect, mAlign, mMeetOrSlice);
        OH_Drawing_CanvasConcatMatrix(canvas, viewBoxMatrix);
        OH_Drawing_MatrixDestroy(viewBoxMatrix);
    }
    
    if (patternContentUnits == Unit::objectBoundingBox) {
        OH_Drawing_CanvasScale(canvas, offsetwidth / scale_, offsetheight / scale_);
    }

    // draw child node
    if (!fillState_.GetHref().empty()) {
        auto svgContext = GetContext();
        auto refSvgNode = svgContext->GetSvgNodeById(fillState_.GetHref());
        CHECK_NULL_VOID(refSvgNode);
        refSvgNode->Draw(canvas);
    }

    OH_Drawing_Matrix *matrix = OH_Drawing_MatrixCreate();
    if (pattern->GetPatternTransform().size() == 9) {
        OH_Drawing_MatrixSetMatrix(matrix, pattern->GetPatternTransform()[0], pattern->GetPatternTransform()[1],
                                   pattern->GetPatternTransform()[2], pattern->GetPatternTransform()[3],
                                   pattern->GetPatternTransform()[4], pattern->GetPatternTransform()[5],
                                   pattern->GetPatternTransform()[6], pattern->GetPatternTransform()[7],
                                   pattern->GetPatternTransform()[8]);
    }

    // set repeat shader
    OH_Drawing_Image *image = OH_Drawing_ImageCreate();
    OH_Drawing_ImageBuildFromBitmap(image, bitmap);

    OH_Drawing_SamplingOptions *opt = OH_Drawing_SamplingOptionsCreate(OH_Drawing_FilterMode::FILTER_MODE_LINEAR,
                                                                       OH_Drawing_MipmapMode::MIPMAP_MODE_NONE);
    OH_Drawing_ShaderEffect *imageShader = OH_Drawing_ShaderEffectCreateImageShader(
        image, OH_Drawing_TileMode::REPEAT, OH_Drawing_TileMode::REPEAT, opt, matrix);
    OH_Drawing_BrushReset(fillBrush_.get());
    OH_Drawing_BrushSetShaderEffect(fillBrush_.get(), imageShader);

    OH_Drawing_CanvasDestroy(canvas);
    OH_Drawing_BitmapDestroy(bitmap);
    OH_Drawing_ImageDestroy(image);
    OH_Drawing_SamplingOptionsDestroy(opt);
    OH_Drawing_MatrixDestroy(matrix);
}

bool SvgGraphic::UpdateStrokeStyle(bool antiAlias) {
    const auto &strokeState = attributes_.strokeState;
    //     auto colorFilter = GetColorFilter();
    //     if (!colorFilter.has_value() && strokeState.GetColor() == Color::TRANSPARENT) {
    //         return false;
    //     }
    if (!GreatNotEqual(strokeState.GetLineWidth(), 0.0)) {
        return false;
    }

    double curOpacity = strokeState.GetOpacity() * attributes_.opacity;
    strokePen_.SetColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    LOG(INFO) << "[svg] strokeState.GetLineCap(): " << static_cast<int>(strokeState.GetLineCap());
    if (strokeState.GetLineCap() == LineCapStyle::ROUND) {
        strokePen_.SetLineCap(LINE_ROUND_CAP);
    } else if (strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        strokePen_.SetLineCap(LINE_SQUARE_CAP);
    } else {
        strokePen_.SetLineCap(LINE_FLAT_CAP);
    }
    LOG(INFO) << "[svg] strokeState.GetLineJoin(): " << static_cast<int>(strokeState.GetLineJoin());
    if (strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        strokePen_.SetLineJoin(LINE_ROUND_JOIN);
    } else if (strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        strokePen_.SetLineJoin(LINE_BEVEL_JOIN);
    } else {
        strokePen_.SetLineJoin(LINE_MITER_JOIN);
    }
    LOG(INFO) << "[SvgRect] OH_Drawing_PenSetWidth: " << strokeState.GetLineWidth();
    strokePen_.SetWidth(strokeState.GetLineWidth());
    strokePen_.SetMiterLimit(strokeState.GetMiterLimit());
    strokePen_.SetAntiAlias(antiAlias);
    //     auto filter = strokePen_.GetFilter();
    //     UpdateColorFilter(filter);
    //     strokePen_.SetFilter(filter);
    UpdateLineDash();
    return true;
}
void SvgGraphic::UpdateLineDash() {
    const auto &strokeState = attributes_.strokeState;
    if (!strokeState.GetStrokeDashArray().empty()) {
        auto lineDashState = strokeState.GetStrokeDashArray();
        float intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<float>(lineDashState[i]);
        }
        float phase = static_cast<float>(strokeState.GetStrokeDashOffset());
        auto *DashPathEffect = OH_Drawing_CreateDashPathEffect(intervals, lineDashState.size(), phase);
        OH_Drawing_PenSetPathEffect(strokePen_.get(), DashPathEffect);
    }
}

void SvgGraphic::DrawMarker(OH_Drawing_Canvas *canvas) {
    auto markerStart = std::dynamic_pointer_cast<SvgMarker>(context_->GetSvgNodeById(attributes_.markerStart));
    auto markerMid = std::dynamic_pointer_cast<SvgMarker>(context_->GetSvgNodeById(attributes_.markerMid));
    auto markerEnd = std::dynamic_pointer_cast<SvgMarker>(context_->GetSvgNodeById(attributes_.markerEnd));
    if (!markerStart && !markerMid && !markerEnd) {
        LOG(WARNING) << "NO MARKER";
        return;
    }
    if (elements_.empty()) {
        LOG(WARNING) << "NO path";
        return;
    }
    std::vector<SvgMarkerPosition> positions = SvgMarkerPositionUtils::fromPath(elements_);
    for (const auto &position : positions) {
        RNSVGMarkerType type = position.type;
        std::shared_ptr<SvgMarker> marker;
        switch (type) {
        case RNSVGMarkerType::kStartMarker:
            marker = markerStart;
            break;

        case RNSVGMarkerType::kMidMarker:
            marker = markerMid;
            break;

        case RNSVGMarkerType::kEndMarker:
            marker = markerEnd;
            break;
        default:
            break;
        }
        if (!marker) {
            continue;
        }
        LOG(INFO) << "DRAW MARKER at " << position.origin.x << " " << position.origin.y
                  << "] type: " << static_cast<int>(type);
        marker->renderMarker(canvas, position, attributes_.strokeState.GetLineWidth());
    }
}

} // namespace svg
} // namespace rnoh