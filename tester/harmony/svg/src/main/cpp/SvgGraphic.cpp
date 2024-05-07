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

namespace rnoh {

void SvgGraphic::OnDraw(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[SVGGraphic] onDraw";
    //     OH_Drawing_BrushReset(fillBrush_);
    //     OH_Drawing_PenReset(strokePen_);
    // 获取子类的绘制路径。
    path_ = AsPath();
    if (UpdateFillStyle()) {
        OnGraphicFill(canvas);
    }
//     OnGraphicFill(canvas);
    UpdateStrokeStyle();
    OnGraphicStroke(canvas);
}
bool SvgGraphic::UpdateFillStyle(bool antiAlias) {
    const auto &fillState_ = attributes_.fillState;
    if (fillState_.GetColor() == Color::TRANSPARENT && !fillState_.GetGradient()) {
        return false;
    }
    double curOpacity = fillState_.GetOpacity() * opacity_ * (1.0f / UINT8_MAX);
    OH_Drawing_BrushSetAntiAlias(fillBrush_,antiAlias);
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
//     auto gradient = fillState_.GetGradient();
//     CHECK_NULL_VOID(gradient);
//     auto gradientColors = gradient->GetColors();
//     if (gradientColors.empty()) {
//         return;
//     }
//     std::vector<RSScalar> pos;
//     std::vector<RSColorQuad> colors;
//     for (const auto &gradientColor : gradientColors) {
//         pos.push_back(static_cast<RSScalar>(gradientColor.GetDimension().Value()));
//         colors.push_back(
//             gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
//     }
//     if (gradient->GetType() == GradientType::LINEAR) {
//         auto info = gradient->GetLinearGradientInfo();
//         std::array<RSPoint, 2> pts = {RSPoint(static_cast<RSScalar>(info.x1), static_cast<RSScalar>(info.y1)),
//                                       RSPoint(static_cast<RSScalar>(info.x2), static_cast<RSScalar>(info.y2))};
//         fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
//             pts[0], pts[1], colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
//     }
//     if (gradient->GetType() == GradientType::RADIAL) {
//         auto info = gradient->GetRadialGradientInfo();
//         auto center = RSPoint(static_cast<RSScalar>(info.cx), static_cast<RSScalar>(info.cy));
//         auto focal = RSPoint(static_cast<RSScalar>(info.fx), static_cast<RSScalar>(info.fx));
//         if (center == focal) {
//             fillBrush_.SetShaderEffect(
//                 RSRecordingShaderEffect::CreateRadialGradient(center, static_cast<RSScalar>(info.r), colors, pos,
//                                                               static_cast<RSTileMode>(gradient->GetSpreadMethod())));
//         } else {
//             RSMatrix matrix;
//             fillBrush_.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(
//                 focal, 0, center, static_cast<RSScalar>(info.r), colors, pos,
//                 static_cast<RSTileMode>(gradient->GetSpreadMethod()), &matrix));
//         }
//     }
}

bool SvgGraphic::UpdateStrokeStyle(bool antiAlias) {
    const auto &strokeState = attributes_.strokeState;
    //     auto colorFilter = GetColorFilter();
    //     if (!colorFilter.has_value() && strokeState.GetColor() == Color::TRANSPARENT) {
    //         return false;
    //     }
    if (!GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        return false;
    }

    double curOpacity = strokeState.GetOpacity() * opacity_ * (1.0f / UINT8_MAX);
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
    LOG(INFO) << "[SvgRect] OH_Drawing_PenSetWidth: " << strokeState.GetLineWidth().GetNativeValue(DimensionUnit::PX);
    OH_Drawing_PenSetWidth(strokePen_, strokeState.GetLineWidth().GetNativeValue(DimensionUnit::PX));

    //     strokePen_.SetMiterLimit(static_cast<RSScalar>(strokeState.GetMiterLimit()));
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
    if (!strokeState.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState.GetLineDash().lineDash;
        float intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<float>(lineDashState[i]);
        }
        float phase = static_cast<float>(strokeState.GetLineDash().dashOffset);
        auto *DashPathEffect = OH_Drawing_CreateDashPathEffect(intervals, lineDashState.size(), phase);
        OH_Drawing_PenSetPathEffect(strokePen_, DashPathEffect);
    }
}

} // namespace rnoh
