/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGSvgViewComponentInstance.h"
#include "RNSVGGroupComponentInstance.h"
#include <glog/logging.h>
namespace rnoh {
namespace svg {

RNSVGSvgViewComponentInstance::RNSVGSvgViewComponentInstance(Context context)
    : CppComponentInstance(std::move(context)) {
    SetSvgNode(m_svgSvg);
    getLocalRootArkUINode().SetSvgNode(GetSvgNode());
    GetSvgNode()->SetContext(std::make_shared<SvgContext>());
    SvgViewManager::getInstance().setSvgView(CppComponentInstance::getTag(), m_svgSvg);
}

RNSVGSvgViewComponentInstance::~RNSVGSvgViewComponentInstance() {
    SvgViewManager::getInstance().onDropView(CppComponentInstance::getTag());
    noSvgComponentIndex = 0;	
}

void RNSVGSvgViewComponentInstance::onFinalizeUpdates() {
    ComponentInstance::onFinalizeUpdates();
    LOG(INFO) << "[SvgView] m_props->bbWidth: " << m_props->bbWidth << ", bbHeight: " << m_props->bbHeight
              << ", minX: " << m_props->minX << ", minY: " << m_props->minY << ", vbWidth: " << m_props->vbWidth
              << ", vbHeight: " << m_props->vbHeight;
    m_svgSvg->SetScale(m_layoutMetrics.pointScaleFactor);
    auto tintColor = getColorFromDynamic(m_props->rawProps);
    if (tintColor.has_value()) {
        m_svgSvg->GetContext()->SetSvgColor(Color::FromString(tintColor.value()));
    }
    m_svgSvg->SetVbX(m_props->minX);
    m_svgSvg->SetVbY(m_props->minY);
    m_svgSvg->SetVbWidth(m_props->vbWidth);
    m_svgSvg->SetVbHeight(m_props->vbHeight);
    m_svgSvg->SetX(0);
    m_svgSvg->SetY(0);
    m_svgSvg->SetWidth(m_props->bbWidth);
    m_svgSvg->SetHeight(m_props->bbHeight);
    m_svgSvg->SetAlign(m_props->align);
    m_svgSvg->SetMeetOrSlice(m_props->meetOrSlice);
    getLocalRootArkUINode().markDirty();
}

void RNSVGSvgViewComponentInstance::onDrawForeignImage(OH_PixelmapNative *foreignPixelMap, float width, float height,
                                                       float x, float y) {
    if (foreignPixelMap) {
        DLOG(INFO) << "[svgForeignNode] RNSVGSvgViewComponentInstance OH_PixelmapNative is not null, position:{ x:" << x
                   << ",y:" << y << "},width:" << width << ";height:" << height;
        m_svgArkUINode.SetForeignObject(foreignPixelMap, width, height, x, y);
        m_svgArkUINode.markDirty();
    } else {
        DLOG(INFO) << "RNSVGSvgViewComponentInstance OH_PixelmapNative is null";
    }
}
void RNSVGSvgViewComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                    std::size_t index) {
    CppComponentInstance::onChildInserted(childComponentInstance, index);
    if (childComponentInstance->getComponentName() == "RNSVGGroup") {
        auto childInstance = childComponentInstance->getChildren();
        for (ComponentInstance::Shared c : childInstance) {
            if (c->getComponentName().find("SVG") == std::string::npos) {
                NativeNodeApi::getInstance()->insertChildAt(m_svgArkUINode.getArkUINodeHandle(),
                                                            c->getLocalRootArkUINode().getArkUINodeHandle(), noSvgComponentIndex);
                noSvgComponentIndex++;															
            }
            auto groupChildInstance = c->getChildren();
            for (ComponentInstance::Shared c1 : groupChildInstance) {
                if (c1->getComponentName() == "RNSVGForeignObject") {
                    auto m_foreignComponentInstance =
                        std::dynamic_pointer_cast<RNSVGForeignObjectComponentInstance>(c1);
                    if (m_foreignComponentInstance) {
                        auto groupInstance =
                            std::dynamic_pointer_cast<RNSVGGroupComponentInstance>(c1->getParent().lock());
                        m_svgArkUINode.SetGroupNode(groupInstance->getNode());
                        m_svgArkUINode.AddChild(m_foreignComponentInstance->getLocalRootArkUINode());
                        m_foreignComponentInstance->getLocalRootArkUINode().SetForeignNodeDelegate(this);
                    }
                }
            }
        }
    }


    OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
}

void RNSVGSvgViewComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
    CppComponentInstance::onChildRemoved(childComponentInstance);
    OnChildRemoveCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
}

SvgArkUINode &RNSVGSvgViewComponentInstance::getLocalRootArkUINode() { return m_svgArkUINode; }

std::optional<std::string> RNSVGSvgViewComponentInstance::getColorFromDynamic(folly::dynamic value) {
    auto rawPropsColor = (value.count("color") > 0) ? std::optional(value["color"].asString()) : std::nullopt;
    return rawPropsColor;
}

bool RNSVGSvgViewComponentInstance::canHandleTouch() const {
    if (m_props != nullptr) {
        auto props = std::dynamic_pointer_cast<const facebook::react::RNSVGSvgViewProps>(m_props);
        return props->pointerEvents == "auto" || props->pointerEvents == "box-only" || props->pointerEvents.size() == 0;
    }
    return true;
};

bool RNSVGSvgViewComponentInstance::canChildrenHandleTouch() const {
    if (m_props != nullptr) {
        auto props = std::dynamic_pointer_cast<const facebook::react::RNSVGSvgViewProps>(m_props);
        return props->pointerEvents == "auto" || props->pointerEvents == "box-none" || props->pointerEvents.size() == 0;
    }
    return true;
};

} // namespace svg
} // namespace rnoh
