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


#include "SvgPattern.h"

namespace rnoh {

SvgPattern::SvgPattern() { LOG(INFO) << "[SvgPattern] init"; }

void SvgPattern::OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[pattern] OnDrawTraversedBefore";
    // 1.
}

void SvgPattern::OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[pattern] OnDrawTraversedAfter";
}

const Pattern &SvgPattern::GetPatternAttr() const { return pattern; }

void SvgPattern::setPatternX(Dimension x) { 
    pattern.setPatternX(x); 
}

void SvgPattern::setPatternY(Dimension y) { 
    pattern.setPatternY(y);
}

void SvgPattern::setHeight(Dimension height) {
    pattern.setHeight(height); 
}

void SvgPattern::setWidth(Dimension width) { 
    pattern.setWidth(width); 
}

void SvgPattern::setPatternContentUnits(int patternContentUnits) {
    pattern.setPatternContentUnits(patternContentUnits); 
}

void SvgPattern::setPatternUnits(int patternUnits) { 
    pattern.setPatternUnits(patternUnits);
}


void SvgPattern::setViewBox(Rect viewBox) { 
    pattern.setViewBox(viewBox);
}

void SvgPattern::setmMinX(float mMinX) { 
    pattern.setmMinX(mMinX);
}

void SvgPattern::setmMinY(float mMinY) { 
    pattern.setmMinY(mMinY);
}

void SvgPattern::setmVbWidth(float mVbWidth) { 
    pattern.setmVbWidth(mVbWidth);
}

void SvgPattern::setmVbHeight(float mVbHeight) { 
    pattern.setmVbHeight(mVbHeight);
}

void SvgPattern::setmAlign(std::string mAlign) { 
    pattern.setmAlign(mAlign);
}

void SvgPattern::setmMeetOrSlice(int mMeetOrSlice) { 
    pattern.setmMeetOrSlice(mMeetOrSlice);
}

void SvgPattern::setPatternTransforms(std::vector<Float> patternTransforms) {
    std::vector<Float> newMatrix {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };
    if (patternTransforms.size() == 6) {
        newMatrix[0] = (Float) patternTransforms[0];
        newMatrix[1] = (Float) patternTransforms[2];
        newMatrix[2] = (Float) patternTransforms[4] * scale_;
        newMatrix[3] = (Float) patternTransforms[1];
        newMatrix[4] = (Float) patternTransforms[3];
        newMatrix[5] = (Float) patternTransforms[5] * scale_;
        pattern.setPatternTransform(std::move(newMatrix));
    }
}

void SvgPattern::setImage(OH_Drawing_Image* image) { pattern.setImage(image); }
} // namespace rnoh