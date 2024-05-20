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
namespace svg {


drawing::Path SvgCircle::AsPath() {
    LOG(INFO) << "[SvgCircle] AsPath";
    // TODO implement ConvertDimensionToPx
    float x;
    float y;
    float r;
    auto nodeBounds = GetRootViewBox();
    if (circleAttribute_.cx.Unit() == DimensionUnit::PERCENT) {
        x = nodeBounds.Left() + circleAttribute_.cx.ConvertToPx(nodeBounds.Width());
    } else {
        x = circleAttribute_.cx.ConvertToPx(nodeBounds.Width());
    }
    if (circleAttribute_.cy.Unit() == DimensionUnit::PERCENT) {
        y = nodeBounds.Top() + circleAttribute_.cy.ConvertToPx(nodeBounds.Height());
    } else {
        y = circleAttribute_.cy.ConvertToPx(nodeBounds.Height());
    }
    r = circleAttribute_.r.ConvertToPx(nodeBounds.Width() > nodeBounds.Height() ? nodeBounds.Height() : nodeBounds.Width());
    path_.AddCircle(x, y, r, PATH_DIRECTION_CW);
    
    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x, y - r)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y - r), Point(x + r, y)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x + r, y), Point(x, y + r)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y + r), Point(x - r, y)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x - r, y), Point(x, y - r)})};
    return path_;
}

void SvgCircle::SetX(const std::string& x) {
    circleAttribute_.cx = SvgAttributesParser::ParseDimension(x, true);
}

void SvgCircle::SetY(const std::string& y) {
    circleAttribute_.cy = SvgAttributesParser::ParseDimension(y, true);
}

void SvgCircle::SetR(const std::string& r) {
    circleAttribute_.r = SvgAttributesParser::ParseDimension(r, true);
}

} // namespace svg
} // namespace rnoh
