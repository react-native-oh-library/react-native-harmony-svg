#pragma once
#include "SvgNode.h"
#include "properties/Font.h"

namespace rnoh {

class SvgGroup : virtual public SvgNode {

public:
    SvgGroup() : SvgNode() { InitGroupFlag(); }
    ~SvgGroup() override = default;

    template <typename T>
    void UpdateFontProps(const std::shared_ptr<T> &props) {
        fp_.fontStyle = props->font.fontStyle;
        fp_.fontVariant = props->font.fontVariant;
        fp_.fontWeight = props->font.fontWeight;
        fp_.fontStretch = props->font.fontStretch;
        fp_.fontSize = props->font.fontSize;
        fp_.fontFamily = props->font.fontFamily;
        fp_.textAnchor = props->font.textAnchor;
        fp_.textDecoration = props->font.textDecoration;
        fp_.letterSpacing = props->font.letterSpacing;
        fp_.wordSpacing = props->font.wordSpacing;
        fp_.kerning = props->font.kerning;
        fp_.fontFeatureSettings = props->font.fontFeatureSettings;
        fp_.fontVariantLigatures = props->font.fontVariantLigatures;
        fp_.fontVariationSettings = props->font.fontVariationSettings;
    }

protected:
    std::shared_ptr<FontData> font_;

private:
    // svg g, use
    void InitGroupFlag();

    void OnInitStyle() override;

    void InheritFont(const std::shared_ptr<FontData> &parent);

    FontProps fp_; // save intermediate font properties here because tree is not ready during onPropsChanged
};

} // namespace rnoh
