/*
 * Copyright (c) 2025 Huawei Device Co., Ltd. All rights reserved
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

#ifndef HARMONY_FOREIGNPROPS_H
#define HARMONY_FOREIGNPROPS_H
#include <multimedia/image_framework/image/pixelmap_native.h>
#include <string>
struct ForeignProps {
    OH_PixelmapNative *foreignPixelMap{nullptr};
    float width;
    float height;
    float x;
    float y;
    std::string path;
    int clipRule;
    std::string mask;
};
#endif //HARMONY_FOREIGNPROPS_H
