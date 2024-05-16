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

#include "SvgEllipse.h"

namespace rnoh {
namespace svg {

drawing::Path SvgEllipse::AsPath() {
    LOG(INFO) << "[SvgEllipse] AsPath";

    auto rect = OH_Drawing_RectCreate(vpToPx(cx - rx), vpToPx(cy - ry), vpToPx(cx + rx), vpToPx(cy + ry));
    OH_Drawing_PathAddOval(path_.get(), rect, PATH_DIRECTION_CW);

    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(cx, cy - ry)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx, cy - ry), Point(cx + rx, cy)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx + rx, cy), Point(cx, cy + ry)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx, cy + ry), Point(cx - rx, cy)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx - rx, cy), Point(cx, cy - ry)})};
    return path_;
};

} // namespace svg
} // namespace rnoh