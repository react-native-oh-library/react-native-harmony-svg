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
#include <native_drawing/drawing_point.h>

namespace rnoh {

class SvgCircle : public SvgGraphic {
public:
    SvgCircle() = default;
    ~SvgCircle() override = default;
    float x;
    float y;
    float r;
    OH_Drawing_Path *AsPath() override;
};

} // namespace rnoh
