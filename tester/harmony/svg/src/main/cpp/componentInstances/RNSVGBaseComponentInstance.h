/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNOH/CppComponentInstance.h"
#include "RNSVGSvgViewComponentInstance.h"
#include "SvgArkUINode.h"
#include "SvgHost.h"
#include "utils/StringUtils.h"
#include <glog/logging.h>

namespace rnoh {
namespace svg {

template <typename T> class RNSVGBaseComponentInstance : public CppComponentInstance<T>, public SvgHost {
public:
    RNSVGBaseComponentInstance(ComponentInstance::Context context) : CppComponentInstance<T>(std::move(context)) {}

    void onPropsChanged(typename CppComponentInstance<T>::SharedConcreteProps const &props) override {
        pointerEvents_ = props->pointerEvents.size() == 0 ? "auto" : props->pointerEvents;
    }

    void onFinalizeUpdates() override {
        if (GetSvgNode()) {
            GetSvgNode()->SetScale(CppComponentInstance<T>::m_layoutMetrics.pointScaleFactor);
        }
        UpdateElementProps();
        svgMarkDirty();
    }

    void onCreate() {}

    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {
        CppComponentInstance<T>::onChildRemoved(childComponentInstance);
        OnChildRemoveCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        CppComponentInstance<T>::onChildInserted(childComponentInstance, index);
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    void setLayout(facebook::react::LayoutMetrics layoutMetrics) override {
        CppComponentInstance<T>::m_layoutMetrics = layoutMetrics;
    };

    std::shared_ptr<RNSVGSvgViewComponentInstance> getParentSvgView() const {
        auto parent = CppComponentInstance<T>::getParent().lock();
        while (parent) {
            auto svgView = std::dynamic_pointer_cast<RNSVGSvgViewComponentInstance>(parent);
            if (svgView) {
                return svgView;
            }
            parent = parent->getParent().lock();
        }
        return nullptr;
    }

    void svgMarkDirty() {
        auto svgView = m_svgViewComponentInstance.lock();
        if (svgView == nullptr) {
            svgView = getParentSvgView();
        }
        if (svgView != nullptr) {
            m_svgViewComponentInstance = svgView;
            svgView->getLocalRootArkUINode().markDirty();
        }
    }

    /*
    check if it can handle the touch itself.
    */
    bool containsPoint(facebook::react::Point const &point) const override {
        if (isInvisible(CppComponentInstance<T>::getComponentName())) {
            return false;
        }
        auto const &node = SvgHost::GetSvgNode();
        if (node == nullptr) {
            return false;
        }
        DLOG(INFO) << "[SvgTouch] name: " << CppComponentInstance<T>::getComponentName();
        // For debug
        auto rect = node->AsBounds();
        DLOG(INFO) << "[SvgTouch] asBound x: " << rect.Left() << ", y: " << rect.Top() << ", width: " << rect.Width()
                   << ", height: " << rect.Height();

        auto invertedTransform = node->lastCanvasMatrix_.Invert();
        if (!invertedTransform.has_value()) {
            return false;
        }
        auto transformed = invertedTransform.value().MapPoint(
            {float(CppComponentInstance<T>::m_layoutMetrics.pointScaleFactor * point.x),
             float(CppComponentInstance<T>::m_layoutMetrics.pointScaleFactor * point.y)});
        return node->AsPath().Contains(transformed.x, transformed.y);
    }

    /*
    check if any of its children can potentially handle the touch (the "bounding box" is a rectangle which contains the
    component and all of its children -- if overflow is visible, they can extend beyond the View, so this is an
    optimization to avoid walking the whole component tree). It also calls canChildrenHandleTouch to check for other
    reasons why it shouldn't check its children (such as pointer events).
    Can just return true from it since it's only used as an optimization to avoid walking the whole tree.
    */
    bool containsPointInBoundingBox(facebook::react::Point const &point) override {
        if (isInvisible(CppComponentInstance<T>::getComponentName())) {
            return false;
        }
        return true;
    }

    std::vector<TouchTarget::Shared> getTouchTargetChildren() override {
        auto children = CppComponentInstance<T>::getChildren();
        return std::vector<TouchTarget::Shared>(children.begin(), children.end());
    }

    facebook::react::Transform getTransform() const override { return facebook::react::Transform::Identity(); }

    facebook::react::Point computeChildPoint(facebook::react::Point const &point,
                                             TouchTarget::Shared const &child) const override {
        return point;
    }

    bool canHandleTouch() const override {
        if (isInvisible(CppComponentInstance<T>::getComponentName())) {
            return false;
        }
        if (CppComponentInstance<T>::m_props != nullptr) {
            return pointerEvents_ == "auto" || pointerEvents_ == "box-only" || pointerEvents_ == "box-none";
        }
        return true;
    };

    bool canChildrenHandleTouch() const override {
        if (isInvisible(CppComponentInstance<T>::getComponentName())) {
            return false;
        }
        if (CppComponentInstance<T>::m_props != nullptr) {
            return pointerEvents_ == "auto" || pointerEvents_ == "box-none";
        }
        return true;
    };

    bool isInvisible(const std::string &name) const {
        if (name == "RNSVGLinearGradient") {
            return true;
        }
        if (name == "RNSVGRadialGradient") {
            return true;
        }
        if (name == "RNSVGDefs") {
            return true;
        }
        if (name == "RNSVGClipPath") {
            return true;
        }
        if (name == "RNSVGMask") {
            return true;
        }
        if (name == "RNSVGUse") {
            return true;
        }
        if (name == "RNSVGMarker") {
            return true;
        }
        if (name == "RNSVGPattern") {
            return true;
        }
        if (name == "RNSVGSymbol") {
            return true;
        }
        return false;
    }

protected:
    virtual void UpdateElementProps() = 0;
    SvgArkUINode &getLocalRootArkUINode() override { return getParentSvgView()->getLocalRootArkUINode(); }

private:
    std::weak_ptr<RNSVGSvgViewComponentInstance> m_svgViewComponentInstance;
    std::string pointerEvents_ = "auto";

};

} // namespace svg
} // namespace rnoh