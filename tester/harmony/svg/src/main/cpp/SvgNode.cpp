/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 *
 * This file incorporates from the OpenHarmony project, licensed under
 * the Apache License, Version 2.0. Specifically:
 * - [OpenHarmony/arkui_ace_engine] (https://gitee.com/openharmony/arkui_ace_engine)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at:
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include "SvgNode.h"
#include "SvgGradient.h"
#include "SvgPattern.h"
#include "properties/ViewBox.h"
#include "utils/SvgUtils.h"
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_pixel_map.h>
#include <string>

namespace rnoh {
namespace svg {

constexpr size_t MIN_TRANSFORM_SIZE = 6;
constexpr int TRANSFORM_SCALE_X_INDEX = 0;
constexpr int TRANSFORM_SKEW_Y_INDEX = 1;
constexpr int TRANSFORM_SKEW_X_INDEX = 2;
constexpr int TRANSFORM_SCALE_Y_INDEX = 3;
constexpr int TRANSFORM_TRANSLATE_X_INDEX = 4;
constexpr int TRANSFORM_TRANSLATE_Y_INDEX = 5;
constexpr double MATRIX_Z_VALUE = 1.0;

void SvgNode::InitStyle(const SvgBaseAttribute &attr) {
    // reset gradient to null
    attributes_.fillState.SetGradient(std::nullopt, false);
    attributes_.strokeState.SetGradient(std::nullopt, false);
    InheritAttr(attr);
    if (hrefFill_) {
        auto fillHref = attributes_.fillState.GetHref();
        if (!fillHref.empty()) {
            auto gradient = GetGradient(fillHref);
            if (gradient) {
                attributes_.fillState.SetGradient(gradient.value(), true);
            }
            auto pattern = GetPatternAttr(fillHref);
            if (pattern) {
                attributes_.fillState.SetPattern(pattern);
            }
        }
        auto strokeHref = attributes_.strokeState.GetHref();
        if (!strokeHref.empty()) {
            auto gradient = GetGradient(strokeHref);
            if (gradient) {
                attributes_.strokeState.SetGradient(gradient.value(), true);
            }
        }
    }
    OnInitStyle();
    if (passStyle_) {
        for (auto &node : children_) {
            // pass down style only if child inheritStyle_ is true
            node->InitStyle((node->inheritStyle_) ? attributes_ : SvgBaseAttribute());
        }
    }
}

void SvgNode::OnDrawTraversed(OH_Drawing_Canvas *canvas) {
    auto smoothEdge = GetSmoothEdge();
    for (auto &node : children_) {
        if (node && node->drawTraversed_) {
            if (GreatNotEqual(smoothEdge, 0.0f)) {
                node->SetSmoothEdge(smoothEdge);
            }
            node->Draw(canvas);
        }
    }
}

const Rect &SvgNode::GetRootViewBox() const {
    if (!context_) {
        static Rect empty;
        return empty;
    }
    return context_->GetRootViewBox();
}

void SvgNode::OnClipPath(OH_Drawing_Canvas *canvas) {
    DLOG(INFO) << "[SvgNode] Draw OnClipPath enter";
    if (!context_) {
        DLOG(WARNING) << "[SvgNode] OnClipPath: Context is null!";
        return;
    }
    auto refSvgNode = context_->GetSvgNodeById(hrefClipPath_);
    if (!refSvgNode) {
        DLOG(WARNING) << "[SvgNode] OnClipPath: SvgNode is null!";
        return;
    };
    auto clipPath = refSvgNode->AsPath();

    // maybe return optional from AsPath?

    // Set clipRule through Drawing API
    clipPath.SetFillType(attributes_.clipState.GetClipRuleForDraw());
    OH_Drawing_CanvasClipPath(canvas, clipPath.get(), OH_Drawing_CanvasClipOp::INTERSECT, true);
}

void SvgNode::OnMask(OH_Drawing_Canvas *canvas) {
    if (!context_) {
        DLOG(INFO) << "NO CONTEXT";
        return;
    }
    auto refMask = context_->GetSvgNodeById(attributes_.maskId);
    if (!refMask) {
        return;
    };
    refMask->Draw(canvas);
}

void SvgNode::OnTransform(OH_Drawing_Canvas *canvas) {
    // input transfrom: (float scaleX, float skewY, float skewX, float scaleY, float transX, float transY)
    const auto &transform = attributes_.transform;
    /*
    /* (OH_Drawing_Matrix* , float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float
    persp0, float persp1, float persp2 )
    */
    if (!attributes_.strokeState.GetVectorEffect() && transform.size() >= MIN_TRANSFORM_SIZE) {
        cTM_.SetMatrix(transform[TRANSFORM_SCALE_X_INDEX], transform[TRANSFORM_SKEW_X_INDEX],
                       transform[TRANSFORM_TRANSLATE_X_INDEX] * scale_, transform[TRANSFORM_SKEW_Y_INDEX],
                       transform[TRANSFORM_SCALE_Y_INDEX], transform[TRANSFORM_TRANSLATE_Y_INDEX] * scale_, 0, 0,
                       MATRIX_Z_VALUE);
        OH_Drawing_CanvasConcatMatrix(canvas, cTM_.get());
    }
}

std::optional<Gradient> SvgNode::GetGradient(const std::string &href) {
    if (!context_) {
        DLOG(INFO) << "NO CONTEXT";
        return std::nullopt;
    }
    auto refSvgNode = context_->GetSvgNodeById(href);
    CHECK_NULL_RETURN(refSvgNode, std::nullopt);
    auto svgGradient = std::dynamic_pointer_cast<SvgGradient>(refSvgNode);
    if (svgGradient) {
        return std::make_optional(svgGradient->GetGradient());
    }
    return std::nullopt;
}

std::shared_ptr<PatternAttr> SvgNode::GetPatternAttr(const std::string &href) {
    if (!context_) {
        DLOG(INFO) << "NO CONTEXT";
        return nullptr;
    }
    auto refSvgNode = context_->GetSvgNodeById(href);
    CHECK_NULL_RETURN(refSvgNode, nullptr);
    auto svgPattern = std::dynamic_pointer_cast<SvgPattern>(refSvgNode);
    if (svgPattern) {
        return svgPattern->GetPatternAttr();
    }
    return nullptr;
}

void SvgNode::Draw(OH_Drawing_Canvas *canvas) {
    if (!display_) {
        return;
    }
    // mask and filter create extra layers, need to record initial layer count
    const auto count = OH_Drawing_CanvasGetSaveCount(canvas);
    OH_Drawing_CanvasSave(canvas);
    if (!attributes_.transform.empty()) {
        OnTransform(canvas);
    }
    if (!hrefClipPath_.empty()) {
        OnClipPath(canvas);
    }
    if (!attributes_.maskId.empty()) {
        OnMask(canvas);
    }

    OH_Drawing_CanvasGetTotalMatrix(canvas, lastCanvasMatrix_.get());

    OnDraw(canvas);
    // on marker

    OnDrawTraversed(canvas);
    
    if (_foreignPropsArray.size() > 0) {
        for (ForeignProps _foreignProps : _foreignPropsArray) {
            DrawForeignPixelMap(canvas, _foreignProps);
        }
        _foreignPropsArray.clear();
    }
    OH_Drawing_CanvasRestoreToCount(canvas, count);
}

Rect SvgNode::AsBounds() {
    auto path = AsPath();
    auto ohRect = path.GetBounds();
    float x = ohRect.GetLeft();
    float y = ohRect.GetTop();
    float width = ohRect.GetWidth();
    float height = ohRect.GetHeight();
    auto rect = Rect(x, y, width, height);
    return rect;
}

void SvgNode::ContextTraversal() {
    if (!context_) {
        DLOG(INFO) << "NO CONTEXT";
        return;
    }
    if (!attributes_.id.empty()) {
        context_->Push(attributes_.id, shared_from_this());
    }
    for (const auto &child : children_) {
        child->SetContext(context_);
        child->ContextTraversal();
    }
}

double SvgNode::relativeOnWidth(Dimension length) { return length.RelativeConvertToPx(getCanvasWidth(), scale_); }

double SvgNode::relativeOnHeight(Dimension length) { return length.RelativeConvertToPx(getCanvasHeight(), scale_); }

double SvgNode::relativeOnOther(Dimension length) { return length.RelativeConvertToPx(getCanvasDiagonal(), scale_); }

double SvgNode::getCanvasWidth() {
    if (canvasWidth_ != -1) {
        return canvasWidth_;
    }
    // to be done? if root is text root
    if (context_) {
        canvasWidth_ = context_->getCanvasBounds().Width() / context_->getCanvasScaleX();
        return canvasWidth_;
    }
    return 0;
}

double SvgNode::getCanvasHeight() {
    if (canvasHeight_ != -1) {
        return canvasHeight_;
    }
    // to be done? if root is text root
    if (context_) {
        canvasHeight_ = context_->getCanvasBounds().Height() / context_->getCanvasScaleY();
        return canvasHeight_;
    }
    return 0;
}

double SvgNode::getCanvasDiagonal() {
    if (canvasDiagonal_ != -1) {
        return canvasDiagonal_;
    }
    double powX = pow((getCanvasWidth()), 2);
    double powY = pow((getCanvasHeight()), 2);
    canvasDiagonal_ = sqrt(powX + powY) * M_SQRT1_2l;
    return canvasDiagonal_;
}

void SvgNode::DrawForeignPixelMap(OH_Drawing_Canvas *canvas, ForeignProps _foreignProps) {
    if (!_foreignProps.foreignPixelMap) {
        DLOG(INFO) << "[svgForeignNode] foreignPixelMap is null";
        return;
    }
    DLOG(INFO) << "[svgForeignNode] DrawForeignPixelMap  start , width:" << _foreignProps.width;
    OH_Pixelmap_ImageInfo *imageInfo;
    OH_PixelmapImageInfo_Create(&imageInfo);

    OH_PixelmapNative_GetImageInfo(_foreignProps.foreignPixelMap, imageInfo);
    uint32_t originalWidth = 0, originalHeight = 0;
    OH_PixelmapImageInfo_GetWidth(imageInfo, &originalWidth);
    OH_PixelmapImageInfo_GetHeight(imageInfo, &originalHeight);
    OH_PixelmapImageInfo_Release(imageInfo);

    if (originalWidth == 0 || originalHeight == 0) {
        DLOG(WARNING) << "[svgForeignNode] Invalid pixelmap size";
        OH_PixelmapNative_Release(_foreignProps.foreignPixelMap);
        return;
    }

    OH_Drawing_PixelMap *ohPixelMap = OH_Drawing_PixelMapGetFromOhPixelMapNative(_foreignProps.foreignPixelMap);
    if (!ohPixelMap) {
        DLOG(WARNING) << "[svgForeignNode] Failed to get OH_Drawing_PixelMap";
        OH_PixelmapNative_Release(_foreignProps.foreignPixelMap);
        return;
    }

    OH_Drawing_CanvasSave(canvas);

    OH_Drawing_CanvasTranslate(canvas, _foreignProps.x, _foreignProps.y);


    float scaleX = static_cast<float>(_foreignProps.width) / originalWidth;
    float scaleY = static_cast<float>(_foreignProps.height) / originalHeight;
    OH_Drawing_CanvasScale(canvas, 1, 1);

    OH_Drawing_Rect *srcRect = OH_Drawing_RectCreate(0, 0, originalWidth, originalHeight);
    OH_Drawing_Rect *dstRect = OH_Drawing_RectCreate(0, 0, originalWidth, originalHeight);
    OH_Drawing_SamplingOptions *sampling = OH_Drawing_SamplingOptionsCreate(FILTER_MODE_LINEAR, MIPMAP_MODE_LINEAR);
    OH_Drawing_CanvasDrawPixelMapRect(canvas, ohPixelMap, srcRect, dstRect, sampling);


    OH_Drawing_CanvasRestore(canvas);
    OH_Drawing_PixelMapDissolve(ohPixelMap);
    OH_PixelmapNative_Release(_foreignProps.foreignPixelMap);
    OH_Drawing_RectDestroy(srcRect);
    OH_Drawing_RectDestroy(dstRect);
    OH_Drawing_SamplingOptionsDestroy(sampling);

    _foreignProps.foreignPixelMap = nullptr;
    DLOG(INFO) << "[svgForeignNode] DrawForeignPixelMap end";
}

} // namespace svg
} // namespace rnoh