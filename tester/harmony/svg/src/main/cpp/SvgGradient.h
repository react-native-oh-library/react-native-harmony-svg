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

#pragma once

#include "SVGGraphic.h"
#include <native_drawing/drawing_point.h>
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgGradient : public SvgNode {
public:
    using Float = facebook::react::Float;
    explicit SvgGradient(GradientType gradientType);
    ~SvgGradient() override = default;
    
    void OnDraw(OH_Drawing_Canvas *canvas) override;

    void SetAttrX1(const std::string& x1);
    void SetAttrY1(const std::string& y1);
    void SetAttrX2(const std::string& x2);
    void SetAttrY2(const std::string& y2);

    void SetAttrFx(const std::string& fx);
    void SetAttrFy(const std::string& fy);
    void SetAttrCx(const std::string& cx);
    void SetAttrCy(const std::string& cy);
    void SetAttrRx(const std::string& rx);
    void SetAttrRy(const std::string& ry);

    void SetAttrGradient(std::vector<Float> gradient);
    void SetAttrGradientUnits(int gradientUnits);
    void SetAttrGradientTransforms(std::vector<Float> gradientTransforms);

    const Gradient& GetGradient() const;

private:
    SvgGradientAttribute gradientAttr_;
    double scale_ = 3.25;
    DimensionUnit defaultUnit_ = DimensionUnit::VP;
};

} // namespace svg
} // namespace rnoh
