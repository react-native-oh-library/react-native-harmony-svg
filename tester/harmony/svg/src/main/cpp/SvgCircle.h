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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_CIRCLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_CIRCLE_H

#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>

namespace rnoh {

class SvgCircle : public SvgGraphic {
public:
    SvgCircle() = default;
    ~SvgCircle() override = default;
    // onProps changed 进行修改
    float x;
    float y;
    float r;
    float opacity;
    uint32_t colorFill;
    void OnDraw(OH_Drawing_Canvas *canvas) override;
//     OH_Drawing_Path *AsPath() override;

private:
 
    float width_ = 100;
    float height_ = 100;
};

} // namespace rnoh

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_CIRCLE_H