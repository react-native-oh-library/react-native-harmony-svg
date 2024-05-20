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
#include "utils/PathParserUtils.h"
#include <native_drawing/drawing_matrix.h>
#include "drawing/Matrix.h"
#include "utils/PathParserUtils.h"

namespace rnoh {
namespace svg {

void SvgPath::setD(std::string _d) {
    d = _d;
    PathParserUtils parser;
    parser.mScale = scale_;
    // only parser "d" to record the point info
    parser.parse(d.c_str());
    elements_ = parser.elements;
    for (PathElement elem : elements_) {
        for (Point &point : elem.points) {
            point.x *= scale_;
            point.y *= scale_;
        }
    }
}

drawing::Path SvgPath::AsPath() {
    drawing::Matrix matrix;
    /*
    /* (OH_Drawing_Matrix* , float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float
    persp0, float persp1, float persp2 )
    */
    //TODO scale canvas? need to pass canvas in AsPath()
    matrix.SetMatrix(scale_, 0, 0, 0, scale_, 0, 0, 0, 1.0);
    auto path = drawing::Path::BuildFromSvgString(d.c_str());
    if (path.has_value()) {
        path_ = std::move(path.value());
        path_.Transform(matrix);
        return path_;
    }
    return drawing::Path();
}

} // namespace svg
} // namespace rnoh
