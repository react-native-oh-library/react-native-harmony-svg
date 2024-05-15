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

#include "SvgPath.h"
#include <native_drawing/drawing_matrix.h>

namespace rnoh {
namespace svg {

OH_Drawing_Path *SvgPath::AsPath() {
    auto *matrix = OH_Drawing_MatrixCreate();
    /*
    /* (OH_Drawing_Matrix* , float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float
    persp0, float persp1, float persp2 )
    */
    //TODO scale canvas? need to pass canvas in AsPath()
    OH_Drawing_MatrixSetMatrix(matrix, scale_, 0, 0, 0, scale_, 0, 0, 0, 1.0);
    auto isSuccessful =  OH_Drawing_PathBuildFromSvgString(path_, d.c_str());
    if (isSuccessful) {
        OH_Drawing_PathTransform(path_, matrix);
        return path_;
    }
    return OH_Drawing_PathCreate();
}

} // namespace svg
} // namespace rnoh
