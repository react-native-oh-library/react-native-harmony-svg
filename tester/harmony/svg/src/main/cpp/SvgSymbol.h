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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SYMBOL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SYMBOL_H

#include <string>
#include "SvgNode.h"
#include "properties/Rect.h"

namespace rnoh {

class SvgSymbol : public SvgNode {

public:
    std::string id;
    Rect viewBox;

    SvgSymbol() : SvgNode()
    {
        InitDefsFlag();
        
    }

    ~SvgSymbol() override = default;

    void InitDefsFlag()
    {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    OH_Drawing_Path *AsPath() const override
    {
        OH_Drawing_Path *path;
        for (auto child : children_) {
            path = child->AsPath();
        }
        return path;
    }
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SYMBOL_H