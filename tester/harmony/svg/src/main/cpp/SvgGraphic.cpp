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
#include <native_drawing/drawing_path_effect.h>
#include <native_drawing/drawing_shader_effect.h>
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_shader_effect.h>
#include "utils/SvgMarkerPositionUtils.h"
#include "SvgMarker.h"

namespace rnoh {

void SvgGraphic::OnDraw(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[SVGGraphic] onDraw marker = " << attributes_.markerStart << " " << attributes_.markerMid << " " << attributes_.markerEnd;
    //     OH_Drawing_BrushReset(fillBrush_);
    //     OH_Drawing_PenReset(strokePen_);
    // 获取子类的绘制路径。
    path_ = AsPath();
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
// todo implement bounds
void SvgGraphic::UpdateGradient() {
    const auto &fillState_ = attributes_.fillState;
    //     auto &gradient = fillState_.GetGradient();
    std::optional<Gradient> gradient = fillState_.GetGradient();
    CHECK_NULL_VOID(gradient);
    //     auto bounds = AsBounds(viewPort);
    //     auto width = bounds.Width();
    //     auto height = bounds.Height();
    if (gradient->GetType() == GradientType::LINEAR) {
        const auto &linearGradient = gradient->GetLinearGradient();
        auto gradientInfo = LinearGradientInfo();
        //         auto x1 = linearGradient.x1 ? ConvertDimensionToPx(linearGradient.x1.value(), width) : 0.0;
        //         gradientInfo.x1 = x1 + bounds.Left();
        //         gradientInfo.x1 = x1 ;
        //         auto y1 = linearGradient.y1 ? ConvertDimensionToPx(linearGradient.y1.value(), height) : 0.0;
        //         gradientInfo.y1 = y1 + bounds.Top();
        //         gradientInfo.y1 = y1 ;
        //         auto x2 = ConvertDimensionToPx((linearGradient.x2 ? linearGradient.x2.value() : 1.0_pct), width);
        //         gradientInfo.x2 = x2 + bounds.Left();
        //         gradientInfo.x2 = x2 ;
        //         auto y2 = linearGradient.y2 ? ConvertDimensionToPx(linearGradient.y2.value(), height) : 0.0;
        //         gradientInfo.y2 = y2 + bounds.Top();
        gradient->SetLinearGradientInfo(gradientInfo);
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        const auto &radialGradient = gradient->GetRadialGradient();
        auto gradientInfo = RadialGradientInfo();
        //         Dimension radialHorizontalSize = Dimension(radialGradient.radialHorizontalSize.value().Value(),
        //                                                    radialGradient.radialHorizontalSize.value().Unit());
        //         gradientInfo.r = ConvertDimensionToPx(radialGradient.radialHorizontalSize ? radialHorizontalSize :
        //         0.5_pct,
        //                                               sqrt(width * height));
        //         Dimension radialCenterX =
        //             Dimension(radialGradient.radialCenterX.value().Value(),
        //             radialGradient.radialCenterX.value().Unit());
        //         gradientInfo.cx =
        //             ConvertDimensionToPx(radialGradient.radialCenterX ? radialCenterX : 0.5_pct, width) +
        //             bounds.Left();
        //         Dimension radialCenterY =
        //             Dimension(radialGradient.radialCenterY.value().Value(),
        //             radialGradient.radialCenterY.value().Unit());
        //         gradientInfo.cy =
        //             ConvertDimensionToPx(radialGradient.radialCenterY ? radialCenterY : 0.5_pct, height) +
        //             bounds.Top();
        //         if (radialGradient.fRadialCenterX && radialGradient.fRadialCenterX->IsValid()) {
        //             gradientInfo.fx = ConvertDimensionToPx(radialGradient.fRadialCenterX.value(), width) +
        //             bounds.Left();
        //         } else {
        //             gradientInfo.fx = gradientInfo.cx;
        //         }
        //         if (radialGradient.fRadialCenterY && radialGradient.fRadialCenterY->IsValid()) {
        //             gradientInfo.fy = ConvertDimensionToPx(radialGradient.fRadialCenterY.value(), height) +
        //             bounds.Top();
        //         } else {
        //             gradientInfo.fy = gradientInfo.cy;
        //         }
        gradient->SetRadialGradientInfo(gradientInfo);
    }
}
bool SvgGraphic::UpdateFillStyle(bool antiAlias) {
    const auto &fillState_ = attributes_.fillState;
    if (fillState_.GetColor() == Color::TRANSPARENT && !fillState_.GetGradient()) {
        return false;
    }
    double curOpacity = fillState_.GetOpacity() * attributes_.opacity;
    OH_Drawing_BrushSetAntiAlias(fillBrush_, antiAlias);
    if (fillState_.GetGradient()) {
        LOG(INFO) << "[SVGGraphic] SetGradientStyle";
        SetGradientStyle(curOpacity);
    } else {
        //         auto fillColor = (color) ? *color : fillState_.GetColor();
        //         fillBrush_.SetColor(fillColor.BlendOpacity(curOpacity).GetValue());
        OH_Drawing_BrushSetColor(fillBrush_, fillState_.GetColor().BlendOpacity(curOpacity).GetValue());
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
    if (gradient->GetType() == GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        std::array<OH_Drawing_Point *, 2> pts = {
            OH_Drawing_PointCreate(static_cast<float>(info.x1), static_cast<float>(info.y1)),
            OH_Drawing_PointCreate(static_cast<float>(info.x2), static_cast<float>(info.y2))};
        if (gradient->IsValid()) {
            OH_Drawing_BrushSetShaderEffect(fillBrush_,
                                            OH_Drawing_ShaderEffectCreateLinearGradient(
                                                pts[0], pts[1], colors.data(), pos.data(), colors.size(),
                                                static_cast<OH_Drawing_TileMode>(gradient->GetSpreadMethod())));
        }
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = OH_Drawing_PointCreate(static_cast<float>(info.cx), static_cast<float>(info.cy));
        auto focal = OH_Drawing_PointCreate(static_cast<float>(info.fx), static_cast<float>(info.fx));
        if (center == focal) {
            //             fillBrush_.SetShaderEffect(
            //                 RSRecordingShaderEffect::CreateRadialGradient(center, static_cast<RSScalar>(info.r),
            //                 colors, pos,
            //                                                               static_cast<RSTileMode>(gradient->GetSpreadMethod())));
            if (gradient->IsValid()) {
                OH_Drawing_BrushSetShaderEffect(
                    fillBrush_, OH_Drawing_ShaderEffectCreateRadialGradient(
                                    center, static_cast<float>(info.r), colors.data(), pos.data(), colors.size(),
                                    static_cast<OH_Drawing_TileMode>(gradient->GetSpreadMethod())));
            }
        } else {
            // todo Two Point Gradient
            //             RSMatrix matrix;
            //             fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(
            //                 focal, 0, center, static_cast<float>(info.r), colors, pos,
            //                 static_cast<RSTileMode>(gradient->GetSpreadMethod()), &matrix));
        }
    }
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
    //     strokePen_.SetColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    OH_Drawing_PenSetColor(strokePen_, strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    LOG(INFO) << "[svg] strokeState.GetLineCap(): " << static_cast<int>(strokeState.GetLineCap());
    if (strokeState.GetLineCap() == LineCapStyle::ROUND) {
        //             strokePen_.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        OH_Drawing_PenSetCap(strokePen_, LINE_ROUND_CAP);
    } else if (strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        //             strokePen_.SetCapStyle(RSPen::CapStyle::SQUARE_CAP);
        OH_Drawing_PenSetCap(strokePen_, LINE_SQUARE_CAP);
    } else {
        //             strokePen_.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
        OH_Drawing_PenSetCap(strokePen_, LINE_FLAT_CAP);
    }
    LOG(INFO) << "[svg] strokeState.GetLineJoin(): " << static_cast<int>(strokeState.GetLineJoin());
    if (strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        OH_Drawing_PenSetJoin(strokePen_, LINE_ROUND_JOIN);
    } else if (strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        OH_Drawing_PenSetJoin(strokePen_, LINE_BEVEL_JOIN);
    } else {
        OH_Drawing_PenSetJoin(strokePen_, LINE_MITER_JOIN);
    }

    //     strokePen_.SetWidth(static_cast<RSScalar>(strokeState.GetLineWidth().Value()));
    LOG(INFO) << "[SvgRect] OH_Drawing_PenSetWidth: " << strokeState.GetLineWidth();
    OH_Drawing_PenSetWidth(strokePen_, strokeState.GetLineWidth());

    //     strokePen_.SetMiterLimit(static_cast<float>(strokeState.GetMiterLimit()));
    OH_Drawing_PenSetMiterLimit(strokePen_, strokeState.GetMiterLimit());

    //     strokePen_.SetAntiAlias(antiAlias);
    OH_Drawing_PenSetAntiAlias(strokePen_, antiAlias);
    //
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
        OH_Drawing_PenSetPathEffect(strokePen_, DashPathEffect);
    }
}

void SvgGraphic::DrawMarker(OH_Drawing_Canvas *canvas) {
    auto markerStart = dynamic_pointer_cast<SvgMarker>(context_->GetSvgNodeById(attributes_.markerStart));
    auto markerMid = dynamic_pointer_cast<SvgMarker>(context_->GetSvgNodeById(attributes_.markerMid));
    auto markerEnd = dynamic_pointer_cast<SvgMarker>(context_->GetSvgNodeById(attributes_.markerEnd));
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
        LOG(INFO) << "DRAW MARKER at " << position.origin.x << " " << position.origin.y << "] type: " << static_cast<int>(type);
        marker->renderMarker(canvas, position, attributes_.strokeState.GetLineWidth());
    }
}

} // namespace rnoh
