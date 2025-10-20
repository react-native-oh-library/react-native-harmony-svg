/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNOH/CppComponentInstance.h"
#include <folly/dynamic.h>
#include "SvgArkUINode.h"
#include <react/renderer/components/react_native_svg/ShadowNodes.h>
#include "SvgViewManager.h"
#include "SvgSvg.h"
#include "RNSVGForeignObjectComponentInstance.h"

namespace rnoh {
namespace svg {
class RNSVGGroupComponentInstance;
} // namespace svg
} // namespace rnoh


namespace rnoh {
namespace svg {

class RNSVGSvgViewComponentInstance : public CppComponentInstance<facebook::react::RNSVGSvgViewShadowNode>,
                                      public SvgHost , public SvgForeignObjectNodeDelegate {
public:
    explicit RNSVGSvgViewComponentInstance(Context context);
    ~RNSVGSvgViewComponentInstance();

    void onFinalizeUpdates() override;
    void onDrawForeignImage(OH_PixelmapNative *foreignPixelMap,float width,float height,float x,float y) override;
    // get SvgNode from childComponentInstance and set it to root_
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

    SvgArkUINode &getLocalRootArkUINode() override;

    // since we can't get color correctly from props
    std::optional<std::string> getColorFromDynamic(folly::dynamic value);

    bool canHandleTouch() const override;

    bool canChildrenHandleTouch() const override;

private:
    SvgArkUINode m_svgArkUINode;
    std::shared_ptr<SvgSvg> m_svgSvg = std::make_shared<SvgSvg>();
};

} // namespace svg
} // namespace rnoh