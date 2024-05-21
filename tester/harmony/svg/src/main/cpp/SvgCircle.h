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

#include "SvgGraphic.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgCircle : public SvgGraphic {
public:
    SvgCircle() = default;
    ~SvgCircle() override = default;

    void SetX(const std::string &x) { circleAttribute_.cx = SvgAttributesParser::ParseDimension(x, true); }
    void SetY(const std::string &y) { circleAttribute_.cy = SvgAttributesParser::ParseDimension(y, true); }
    void SetR(const std::string &r) { circleAttribute_.r = SvgAttributesParser::ParseDimension(r, true); }
    drawing::Path AsPath() override;
private:
    SvgCircleAttribute circleAttribute_;
};

} // namespace svg
} // namespace rnoh
