/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "FontHolderBase.h"
#include "SvgNode.h"
#include "properties/Font.h"

namespace rnoh {
namespace svg {

class SvgGroup : public SvgNode, public FontHolderBase {

public:
    SvgGroup() : SvgNode() { InitGroupFlag(); }
    ~SvgGroup() override = default;

private:
    // svg g, use
    void InitGroupFlag();

    void OnInitStyle() override;
};

} // namespace svg
} // namespace rnoh
