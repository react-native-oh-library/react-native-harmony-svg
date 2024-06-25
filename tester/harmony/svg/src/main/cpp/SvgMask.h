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

#include "drawing/Rect.h"
#include "properties/Dimension.h"
#include "SvgQuote.h"

namespace rnoh {
namespace svg {

class SvgMask : public SvgQuote {
public:
    SvgMask() = default;
    ~SvgMask() override = default;

    void setMaskX(const std::string &x) {
        maskAttribute_.x = StringUtils::StringToDimensionWithUnit(x, defaultDimensionUnit_);
    }

    void setMaskY(const std::string &y) {
        maskAttribute_.y = StringUtils::StringToDimensionWithUnit(y, defaultDimensionUnit_);
    }

    void setMaskHeight(const std::string &height) {
        maskAttribute_.height = StringUtils::StringToDimensionWithUnit(height, defaultDimensionUnit_);
    }

    void setMaskWidth(const std::string &width) {
        maskAttribute_.width = StringUtils::StringToDimensionWithUnit(width, defaultDimensionUnit_);
    }

    void isDefaultMaskUnits(bool isDefaultMaskUnits) { isDefaultMaskUnits_ = isDefaultMaskUnits; }

    void isDefaultMaskContentUnits(bool isDefaultMaskContentUnits) {
        isDefaultMaskContentUnits_ = isDefaultMaskContentUnits;
    }

    void setMaskUnits(const int &maskUnits) {
        maskAttribute_.maskUnits = ToUnit(maskUnits);
        isDefaultMaskUnits(maskAttribute_.maskUnits == Unit::objectBoundingBox);
    }

    void setMaskContentUnits(const int &maskContentUnits) {
        maskAttribute_.maskContentUnits = ToUnit(maskContentUnits);
        isDefaultMaskContentUnits(maskAttribute_.maskContentUnits == Unit::userSpaceOnUse);
    }
    

protected:
    void OnInitStyle() override;
    void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) override;
    void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) override;
    double ParseUnitsAttr(const Dimension &attr, double value);

private:
    bool isDefaultMaskUnits_ = true;
    bool isDefaultMaskContentUnits_ = true;
    SvgMaskAttribute maskAttribute_;

    drawing::Rect maskBounds_;
    int canvasLayerCount_ = -1;
    DimensionUnit defaultDimensionUnit_ = DimensionUnit::VP;
};

} // namespace svg
} // namespace rnoh