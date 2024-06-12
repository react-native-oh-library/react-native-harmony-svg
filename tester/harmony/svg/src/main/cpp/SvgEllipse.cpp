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
#include "drawing/Rect.h"

namespace rnoh {
namespace svg {

drawing::Path SvgEllipse::AsPath() {
    drawing::Path path;
    double cx = relativeOnWidth(ellipseAttribute_.cx);
    double cy = relativeOnHeight(ellipseAttribute_.cy);
    double rx = relativeOnWidth(ellipseAttribute_.rx);
    double ry = relativeOnHeight(ellipseAttribute_.ry);

    drawing::Rect rect(cx - rx, cy - ry, cx + rx, cy + ry);
    path.AddOval(rect, PATH_DIRECTION_CW);

    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(cx, cy - ry)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx, cy - ry), Point(cx + rx, cy)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx + rx, cy), Point(cx, cy + ry)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx, cy + ry), Point(cx - rx, cy)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx - rx, cy), Point(cx, cy - ry)})};
    return path;
};

} // namespace svg
} // namespace rnoh