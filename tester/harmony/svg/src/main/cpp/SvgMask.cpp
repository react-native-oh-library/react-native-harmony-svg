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

#include "SvgMask.h"

namespace rnoh {

void SvgMask::OnDrawTraversedBefore(OH_Drawing_Canvas* canvas)
{
     LOG(INFO) << "[RNSVGMask] OnDrawTraversedBefore";
     // todo: need to finish AsBounds
          auto nodeBounds = isDefaultMaskUnits_ ? AsBounds() : GetRootViewBox();
          float left = static_cast<float>(nodeBounds.Left() + ParseUnitsAttr(x_, nodeBounds.Width()));
          float top = static_cast<float>(nodeBounds.Top() + ParseUnitsAttr(y_, nodeBounds.Height()));
          float width = static_cast<float>(ParseUnitsAttr(width_, nodeBounds.Width()));
          float height = static_cast<float>(ParseUnitsAttr(height_, nodeBounds.Height()));
          auto maskBounds_ = OH_Drawing_RectCreate(left, top, width + left, height + top);
//           auto maskBounds_ = OH_Drawing_RectCreate(30, 30, 60, 60);

     // create mask layer
     OH_Drawing_CanvasSaveLayer(canvas, maskBounds_, nullptr);
     // ready to render mask content
     canvasLayerCount_ = OH_Drawing_CanvasGetSaveCount(canvas);
    
     // set mask
     auto outerFilter = OH_Drawing_ColorFilterCreateLuma();
     auto innerFilter = OH_Drawing_ColorFilterCreateSrgbGammaToLinear();
     auto colorFilter = OH_Drawing_ColorFilterCreateCompose(outerFilter, innerFilter);
     auto *filter = OH_Drawing_FilterCreate();
     OH_Drawing_FilterSetColorFilter(filter, colorFilter);

     auto *mask_filter = OH_Drawing_BrushCreate();
     OH_Drawing_BrushSetFilter(mask_filter, filter);
     OH_Drawing_CanvasSaveLayer(canvas, nullptr, mask_filter);
}

void SvgMask::OnDrawTraversedAfter(OH_Drawing_Canvas* canvas)
{
    LOG(INFO) << "[RNSVGMask] OnDrawTraversedAfter";
    OH_Drawing_CanvasRestoreToCount(canvas, canvasLayerCount_);
    // create content layer and render content
    auto *maskBrush = OH_Drawing_BrushCreate();
    OH_Drawing_BrushSetBlendMode(maskBrush, BLEND_MODE_SRC_IN);

    OH_Drawing_CanvasSaveLayer(canvas, maskBounds_, maskBrush);
    OH_Drawing_CanvasClipRect(canvas, maskBounds_, INTERSECT, true);
}


void SvgMask::OnInitStyle()
{
    LOG(INFO) << "[RNSVGMask] OnInitStyle";
    // todo: need to finish SvgMaskDeclaration
//     auto declaration = Ace::AceType::DynamicCast<SvgMaskDeclaration>(declaration_);
//     CHECK_NULL_VOID(declaration);
//     isDefaultMaskUnits_ = (declaration->GetMaskUnits() == "objectBoundingBox");
//     isDefaultMaskContentUnits_ = (declaration->GetMaskContentUnits() == "userSpaceOnUse");
//     x_ = declaration->GetX();
//     y_ = declaration->GetY();
//     height_ = declaration->GetHeight();
//     width_ = declaration->GetWidth();
}

 double SvgMask::ParseUnitsAttr(const Dimension &attr, double value) {
    LOG(INFO) << "[RNSVGMask] ParseUnitsAttr";
    if (isDefaultMaskUnits_) {
        // only support decimal or percent
        if (attr.Unit() == DimensionUnit::PERCENT) {
            return value * attr.Value();
        }
        return attr.Value() * value;
       }
       // percent and px
       if (attr.Unit() == DimensionUnit::PERCENT) {
           return value * attr.Value();
       }
       return attr.Value();
 }

 Rect SvgMask::AsBounds() {
    return {60, 60, 450, 450};
 }
 } // namespace rnoh


