// from ArkUI "frameworks/core/components/declaration/svg/svg_base_declaration.h"
#pragma once

#include "Attribute.h"
#include "properties/SvgPaintState.h"
#include <string>
#include <vector>

namespace rnoh {

const char VALUE_NONE[] = "none";

struct SvgBaseAttribute : Attribute {
    double selfOpacity = 1.0; // opacity declared in tag attribute
    double opacity = 1.0; // multiplied with parent opacity. The actual opacity to be drawn
    float smoothEdge = 0.0f;
    FillState fillState;
    StrokeState strokeState;
//     SvgTextStyle textStyle;
    std::vector<double> transform; // transform matrix
    std::string transformOrigin;
    std::string filterId;
    std::string maskId;
    std::string id;
    std::string markerStart;
    std::string markerMid;
    std::string markerEnd;
    std::string clipPath;
//     ClipState clipState;

    void InheritFromUse(const SvgBaseAttribute& parent)
    {
        opacity = selfOpacity * parent.opacity;
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
//         clipState.Inherit(parent.clipState);
    }

    void Inherit(const SvgBaseAttribute& parent)
    {
        opacity = selfOpacity * parent.opacity;
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
//         clipState.Inherit(parent.clipState);
    }
};

// class SvgBaseDeclaration : public Declaration {
//     DECLARE_ACE_TYPE(SvgBaseDeclaration, Declaration);
//
// public:
//     SvgBaseDeclaration() = default;
//     ~SvgBaseDeclaration() override = default;
//
//     const FillState& GetFillState() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.fillState;
//     }
//
//     const StrokeState& GetStrokeState() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.strokeState;
//     }
//
//     const SvgTextStyle& GetSvgTextStyle() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.textStyle;
//     }
//
//     const std::string& GetTransform() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.transform;
//     }
//
//     const std::string& GetMaskId() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.maskId;
//     }
//
//     const std::string& GetFilterId() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.filterId;
//     }
//
//     const std::string& GetTransformOrigin() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.transformOrigin;
//     }
//
//     bool HasOpacity() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.hasOpacity;
//     }
//
//     double GetOpacity() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.opacity;
//     }
//
//     void Inherit(const RefPtr<Declaration>& parent);
//
//     void SetGradient(const Gradient& gradient)
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         attribute.fillState.SetGradient(gradient);
//     }
//
//     const std::string& GetClipPathHref() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.clipState.GetHref();
//     }
//
//
//     const ClipState& GetClipState() const
//     {
//         auto& attribute = static_cast<SvgBaseAttribute&>(GetAttribute(AttributeTag::SPECIALIZED_ATTR));
//         return attribute.clipState;
//     }
//
//     const std::string& GetId()
//     {
//         auto& commonAttr = MaybeResetAttribute<CommonAttribute>(AttributeTag::COMMON_ATTR);
//         return commonAttr.id;
//     }
//
//     LineCapStyle GetLineCapStyle(const std::string& val) const;
//     LineJoinStyle GetLineJoinStyle(const std::string& val) const;
//     Color GetColor(const std::string& value) const;
//
//     bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
//
//     void ReplaceAttributes(const SvgBaseAttribute& attr);
//
// protected:
//     void InitSpecialized() override;
//     bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
//     bool SetPresentationAttr(const std::pair<std::string, std::string>& attr);
// };

} // namespace rnoh
