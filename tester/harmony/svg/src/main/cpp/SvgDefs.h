/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_DEFS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_DEFS_H

#include <string>
#include "SvgNode.h"
#include <native_drawing/drawing_path.h>

namespace rnoh {

class SvgDefs : public SvgNode {

public:
    SvgDefs() : SvgNode()
    {
        InitDefsFlag();
        LOG(INFO) << "[RNSvgDefsComponentInstance]: " ;
    }

    ~SvgDefs() override = default;

    void InitDefsFlag()
    {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    OH_Drawing_Path *AsPath() const override
    {
        auto* path = OH_Drawing_PathCreate();
        for (const auto& child : children_) {
            path = child->AsPath();
        //   path.Op(path, childPath, RSPathOp::UNION);
        }
        return path;
    }
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SYMBOL_H