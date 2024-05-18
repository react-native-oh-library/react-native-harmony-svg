#pragma once
#include "RNOH/CppComponentInstance.h"
#include "ShadowNodes.h"
#include "SvgArkUINode.h"
#include "SvgHost.h"
#include "RNSVGSvgViewComponentInstance.h"
#include "utils/StringUtils.h"

namespace rnoh {
namespace svg {

template <typename T> class RNSVGBaseComponentInstance : public CppComponentInstance<T>, public SvgHost {
public:
    RNSVGBaseComponentInstance(ComponentInstance::Context context) : CppComponentInstance<T>(std::move(context)) {}

    void onPropsChanged(typename CppComponentInstance<T>::SharedConcreteProps const &props) override {
        GetSvgNode()->UpdateCommonProps(props);
        LOG(INFO) << "[SvgTouch] pointerEvents-c++: " << props->pointerEvents;
        LOG(INFO) << "[SvgTouch] pointerEvents-c++: " << props->pointerEvents.size();
        pointerEvents_ = props->pointerEvents.size() == 0 ? "auto" : props->pointerEvents;
        UpdateElementProps(props);
        svgMarkDirty();
    }
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override {}

    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }
    
    void setLayout(facebook::react::LayoutMetrics layoutMetrics) override {};

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
        LOG(INFO) << "[SvgTouch] name: " << CppComponentInstance<T>::getComponentName();
        LOG(INFO) << "[SvgTouch] point x: " << point.x << ", y: " << point.y;
        LOG(INFO) << "[SvgTouch] point PX x1: " << vpToPx(point.x) << ", PX y1: " << vpToPx(point.y);
        LOG(INFO) << "[SvgTouch] containsPoint1: " << SvgHost::GetSvgNode()->AsPath().Contains(vpToPx(point.x), vpToPx(point.y));
        // For debug
        auto rect = SvgHost::GetSvgNode()->AsBounds();
        LOG(INFO) << "[SvgTouch] asBound x: "
                  << rect.Left() << ", y: " << rect.Top() << ", width: " << rect.Width() << ", height: " << rect.Height();
        return SvgHost::GetSvgNode()->AsPath().Contains(vpToPx(point.x), vpToPx(point.y));
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

    facebook::react::Transform getTransform() const override {
        auto matrix = CppComponentInstance<T>::m_props->matrix;
        LOG(INFO) << "[SvgTouch] matrix: " << StringUtils::doubleVectorToString(matrix);
        if (matrix.size() == 6) {
            facebook::react::Transform transform;
            transform.Scale(matrix[0], matrix[3], 1);
            transform.Skew(matrix[2], matrix[1]);
            transform.Translate(matrix[4], matrix[5], 0);
            return transform;
        }
        return facebook::react::Transform::Identity();
    }

    facebook::react::Point computeChildPoint(facebook::react::Point const &point, TouchTarget::Shared const &child) const override {
        auto svgView = m_svgViewComponentInstance.lock();
        facebook::react::LayoutMetrics childLayout;
        if (svgView == nullptr) {
            svgView = getParentSvgView();
        }
        if (svgView != nullptr) {
            auto childLayout = svgView->getLayoutMetrics();
        }
//         auto childLayout = child->getLayoutMetrics();
        auto childTransform = child->getTransform();

        // the center of the view (relative to its origin)
        facebook::react::Point center{childLayout.frame.size.width / 2, childLayout.frame.size.height / 2};
        // the center of the view (before applying its transformation),
        // which is the origin of the transformation (relative to parent)
        facebook::react::Point transformationOrigin = childLayout.frame.origin + center;

        auto inverseTransform = invertTransform(childTransform);
        if (!inverseTransform.has_value()) {
            // if the transform matrix is not invertible, the scale in some direction is
            // 0, and so the point cannot be within the transformed view
            auto infinity = std::numeric_limits<facebook::react::Float>::infinity();
            return {infinity, infinity};
        }

        // transform the vector from the origin of the transformation
        auto transformedOffsetFromCenter =
            (point + this->getCurrentOffset() - transformationOrigin) * inverseTransform.value();

        // add back the offset of the center relative to the origin of the view
        auto localPoint = transformedOffsetFromCenter + center;

        return localPoint;
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

    std::optional<facebook::react::Transform> invertTransform(const facebook::react::Transform &transform) const {
        facebook::react::Transform result;
        auto succeeded = gluInvertMatrix(transform.matrix, result.matrix);
        if (!succeeded) {
            return std::nullopt;
        }
        return result;
    }

    static bool gluInvertMatrix(const std::array<facebook::react::Float, 16> &m,
                                std::array<facebook::react::Float, 16> &invOut) {
        invOut[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
                    m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
        invOut[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
                    m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
        invOut[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
                    m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
        invOut[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
                     m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
        invOut[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
                    m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
        invOut[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
                    m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
        invOut[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
                    m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
        invOut[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
                     m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
        invOut[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
                    m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
        invOut[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
                    m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
        invOut[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
                     m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
        invOut[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
                     m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
        invOut[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
                    m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
        invOut[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
                    m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
        invOut[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
                     m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
        invOut[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +
                     m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

        auto det = m[0] * invOut[0] + m[1] * invOut[4] + m[2] * invOut[8] + m[3] * invOut[12];
        if (det == 0) {
            return false;
        }

        det = 1.0 / det;

        for (size_t i = 0; i < 16; i++) {
            invOut[i] *= det;
        }

        return true;
    }

protected:
    virtual void UpdateElementProps(typename CppComponentInstance<T>::SharedConcreteProps const &props) = 0;
    SvgArkUINode &getLocalRootArkUINode() override { return getParentSvgView()->getLocalRootArkUINode(); }

private:
    std::weak_ptr<RNSVGSvgViewComponentInstance> m_svgViewComponentInstance;
    std::string pointerEvents_ = "auto";
};

} // namespace svg
} // namespace rnoh