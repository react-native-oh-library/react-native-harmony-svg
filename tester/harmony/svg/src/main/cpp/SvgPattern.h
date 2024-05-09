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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_PATTERN_H

#include <string>
#include "SvgQuote.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {

class SvgPattern : public SvgQuote {

public:
    SvgPatternAttribute patternAttr_;
    
    SvgPattern();
    ~SvgPattern() = default;
    
    virtual void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) override;
    virtual void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) override;
    
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_PATTERN_H