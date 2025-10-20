/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */
#ifndef RNSVG_GROUP_COMPONENT_INSTANCE_H
#define RNSVG_GROUP_COMPONENT_INSTANCE_H
#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgGroup.h"

namespace rnoh {
namespace svg {

class RNSVGGroupComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGGroupShadowNode> {
public:
    explicit RNSVGGroupComponentInstance(Context context);
    std::shared_ptr<SvgGroup> getNode(){
        return m_svgGroup;
    }
protected:
    void UpdateElementProps() override;
    
private:
    std::shared_ptr<SvgGroup> m_svgGroup = std::make_shared<SvgGroup>();
};

} // namespace svg
} // namespace rnoh
#endif // RNSVG_GROUP_COMPONENT_INSTANCE_H