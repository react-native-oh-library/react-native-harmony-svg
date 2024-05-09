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

#include <native_drawing/drawing_brush.h>
#include <native_drawing/drawing_color_filter.h>
#include <native_drawing/drawing_filter.h>
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_color.h>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_pen.h>
#include <native_drawing/drawing_rect.h>
#include "properties/Dimension.h"
#include "SvgQuote.h"
#include "properties/Rect.h"

namespace rnoh {

class SvgMask : public SvgQuote {
public:
    SvgMask() = default;
    ~SvgMask() override = default;

    void setMaskX(Dimension x) { x_ = x; }

    void setMaskY(Dimension y) { y_ = y; }

    void setMaskHeight(Dimension height) { height_ = height; }

    void setMaskWidth(Dimension width) { width_ = width; }

    void isDefaultMaskUnits(bool isDefaultMaskUnits) { isDefaultMaskUnits_ = isDefaultMaskUnits; }

    void isDefaultMaskContentUnits(bool isDefaultMaskContentUnits) {
        isDefaultMaskContentUnits_ = isDefaultMaskContentUnits;
    }


protected:
    void OnInitStyle() override;
    void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) override;
    void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) override;
    double ParseUnitsAttr(const Dimension &attr, double value);

    Rect AsBounds();


private:
    Dimension x_ = Dimension(-0.1, DimensionUnit::PERCENT);     // x-axis default value
    Dimension y_ = Dimension(-0.1, DimensionUnit::PERCENT);     // y-axis default value
    Dimension height_ = Dimension(1.2, DimensionUnit::PERCENT); // masking area width default value
    Dimension width_ = Dimension(1.2, DimensionUnit::PERCENT);  // masking area height default  value
    bool isDefaultMaskUnits_ = true;
    bool isDefaultMaskContentUnits_ = true;

    OH_Drawing_Rect *maskBounds_;
    int canvasLayerCount_ = -1;
};

} // namespace rnoh