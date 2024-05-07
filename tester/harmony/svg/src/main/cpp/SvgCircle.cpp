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

#include "SvgCircle.h"

namespace rnoh {
void SvgCircle::OnDraw(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[SVGNode] OnCircle:";
    auto brush = OH_Drawing_BrushCreate();

    OH_Drawing_BrushSetColor(brush, colorFill);
    OH_Drawing_BrushSetAlpha(brush, opacity);

    OH_Drawing_CanvasAttachBrush(canvas, brush);
    auto point = OH_Drawing_PointCreate(vpToPx(x), vpToPx(y));
    // 使用 props属性生成路径。
    OH_Drawing_CanvasDrawCircle(canvas, point, vpToPx(r));
    OH_Drawing_PointDestroy(point);
}

//  OH_Drawing_Path* SvgCircle:: AsPath()  {
//      auto path = OH_Drawing_PathCreate();
//      // 使用 props属性生成路径。
//      float width = width_;
//      float height = height_;
//      OH_Drawing_PathMoveTo(path, width / 4, height / 4);
//      OH_Drawing_PathLineTo(path, width * 3 / 4, height / 4);
//      OH_Drawing_PathLineTo(path, width * 3 / 4, height * 3 / 4);
//      OH_Drawing_PathLineTo(path, width / 4, height * 3 / 4);
//      OH_Drawing_PathLineTo(path, width / 4, height / 4);
//
//
//      OH_Drawing_PathClose(path);
//      return path;
//  }

} // namespace rnoh
