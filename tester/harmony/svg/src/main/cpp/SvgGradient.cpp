/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SvgGradient.h"
#include <native_drawing/drawing_shader_effect.h>
#include "properties/Decoration.h"

namespace rnoh {
namespace svg {

constexpr int TRANSFORM_SCALE_X_INDEX = 0;
constexpr int TRANSFORM_SKEW_Y_INDEX = 1;
constexpr int TRANSFORM_SKEW_X_INDEX = 2;
constexpr int TRANSFORM_SCALE_Y_INDEX = 3;
constexpr int TRANSFORM_TRANSLATE_X_INDEX = 4;
constexpr int TRANSFORM_TRANSLATE_Y_INDEX = 5;
constexpr size_t GRADIENT_TRANSFORM_MATRIX_SIZE = 6;

SvgGradient::SvgGradient(GradientType gradientType)
{
    gradientAttr_.gradient.SetType(gradientType);
    InitNoneFlag();
}

void SvgGradient::OnDraw(OH_Drawing_Canvas *canvas) {
}

void SvgGradient::SetAttrX1(const std::string& x1) {
    gradientAttr_.gradient.GetLinearGradient().x1 = StringUtils::StringToDimensionWithUnit(x1, defaultUnit_);
}

void SvgGradient::SetAttrY1(const std::string& y1) {
    gradientAttr_.gradient.GetLinearGradient().y1 = StringUtils::StringToDimensionWithUnit(y1, defaultUnit_);
}

void SvgGradient::SetAttrX2(const std::string& x2) {
    gradientAttr_.gradient.GetLinearGradient().x2 = StringUtils::StringToDimensionWithUnit(x2, defaultUnit_);
}

void SvgGradient::SetAttrY2(const std::string& y2) {
    gradientAttr_.gradient.GetLinearGradient().y2 = StringUtils::StringToDimensionWithUnit(y2, defaultUnit_);
}

void SvgGradient::SetAttrFx(const std::string& fx) {
    gradientAttr_.gradient.GetRadialGradient().fRadialCenterX = StringUtils::StringToDimensionWithUnit(fx, defaultUnit_);
}

void SvgGradient::SetAttrFy(const std::string& fy) {
    gradientAttr_.gradient.GetRadialGradient().fRadialCenterY = StringUtils::StringToDimensionWithUnit(fy, defaultUnit_);
}

void SvgGradient::SetAttrCx(const std::string& cx) {
    gradientAttr_.gradient.GetRadialGradient().radialCenterX = StringUtils::StringToDimensionWithUnit(cx, defaultUnit_);
}

void SvgGradient::SetAttrCy(const std::string& cy) {
    gradientAttr_.gradient.GetRadialGradient().radialCenterY = StringUtils::StringToDimensionWithUnit(cy, defaultUnit_);
}

void SvgGradient::SetAttrRx(const std::string& rx) {
    gradientAttr_.gradient.GetRadialGradient().radialHorizontalSize = StringUtils::StringToDimensionWithUnit(rx, defaultUnit_);
}

void SvgGradient::SetAttrRy(const std::string& ry) {
    gradientAttr_.gradient.GetRadialGradient().radialVerticalSize = StringUtils::StringToDimensionWithUnit(ry, defaultUnit_);
}

void SvgGradient::SetAttrGradient(std::vector<Float> gradient) {
    auto stopCount = gradient.size() / 2;
    gradientAttr_.gradient.ClearColors();
    for (auto i = 0; i < stopCount; i++) {
        auto stopIndex = i * 2;
        GradientColor gradientColor;
        gradientColor.SetDimension(Dimension(gradient[stopIndex]));
        gradientColor.SetColor(Color((int32_t)gradient[stopIndex + 1]));
        gradientAttr_.gradient.AddColor(gradientColor);
    }
}

void SvgGradient::SetAttrGradientUnits(int gradientUnits) {
    auto unit = static_cast<Unit>(gradientUnits);
    if (unit < Unit::objectBoundingBox || unit > Unit::userSpaceOnUse) {
        unit = Unit::objectBoundingBox;
    }
    gradientAttr_.gradient.SetGradientUnits(ToUnit(gradientUnits));
    defaultUnit_ = (gradientAttr_.gradient.GetGradientUnits() == Unit::objectBoundingBox)
                    ? DimensionUnit::PERCENT
                    : DimensionUnit::VP;
}

void SvgGradient::SetAttrGradientTransforms(std::vector<Float> gradientTransforms) {
    std::vector<Float> newMatrix {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };
    if (gradientTransforms.size() == GRADIENT_TRANSFORM_MATRIX_SIZE) {
        newMatrix[0] = (Float) gradientTransforms[TRANSFORM_SCALE_X_INDEX];
        newMatrix[1] = (Float) gradientTransforms[TRANSFORM_SKEW_X_INDEX];
        newMatrix[2] = (Float) gradientTransforms[TRANSFORM_TRANSLATE_X_INDEX] * scale_;
        newMatrix[3] = (Float) gradientTransforms[TRANSFORM_SKEW_Y_INDEX];
        newMatrix[4] = (Float) gradientTransforms[TRANSFORM_SCALE_Y_INDEX];
        newMatrix[5] = (Float) gradientTransforms[TRANSFORM_TRANSLATE_Y_INDEX] * scale_;
        gradientAttr_.gradient.SetGradientTransform(std::move(newMatrix));
    }
}

const Gradient& SvgGradient::GetGradient() const
{
    return gradientAttr_.gradient;
}

} // namespace svg
} // namespace rnoh
