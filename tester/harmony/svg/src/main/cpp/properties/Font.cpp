#include "Font.h"
#include "utils/StringUtils.h"
#include <algorithm>
namespace rnoh {

double FontData::toAbsolute(const std::string &value, double scale, double fontSize, double relative) {
    auto val = StringUtils::FromString(value);
    return val.ConvertToPx(fontSize);
}

void FontData::setInheritedWeight(const FontData &parent) {
    absoluteFontWeight = parent.absoluteFontWeight;
    fontWeight = parent.fontWeight;
}

void FontData::handleNumericWeight(const FontData &parent, double number) {
    long weight = static_cast<long>(number);
    if (weight >= 1 && weight <= 1000) {
        absoluteFontWeight = static_cast<int>(weight);
        fontWeight = nearestFontWeight(absoluteFontWeight);
    } else {
        setInheritedWeight(parent);
    }
}

FontData::FontData(const FontProps &props, const FontData &parent, double scale) {
    double parentFontSize = parent.fontSize;

    if (!props.fontSize.empty()) {
        fontSize = toAbsolute(props.fontSize, 1, parentFontSize, parentFontSize);
    } else {
        fontSize = parentFontSize;
    }

    if (!props.fontWeight.empty()) {
        fontWeight = fontWeightFromStr(props.fontWeight);
        if (fontWeight != FontWeight::unknown) {
            absoluteFontWeight = from(fontWeight, parent);
            fontWeight = nearestFontWeight(absoluteFontWeight);
        } else {
            handleNumericWeight(parent, StringUtils::FromString(props.fontWeight).Value());
        }
    } else {
        setInheritedWeight(parent);
    }

    fontFamily = !props.fontFamily.empty() ? props.fontFamily : parent.fontFamily;
    fontStyle = !props.fontStyle.empty() ? fontStyleFromStr(props.fontStyle) : parent.fontStyle;
    fontFeatureSettings = !props.fontFeatureSettings.empty() ? props.fontFeatureSettings : parent.fontFeatureSettings;
    fontVariationSettings =
        !props.fontVariationSettings.empty() ? props.fontVariationSettings : parent.fontVariationSettings;
    fontVariantLigatures = !props.fontVariantLigatures.empty() ? fontVariantFromStr(props.fontVariantLigatures)
                                                               : parent.fontVariantLigatures;

    textAnchor = !props.textAnchor.empty() ? textAnchorFromStr(props.textAnchor) : parent.textAnchor;
    textDecoration =
        !props.textDecoration.empty() ? textDecorationFromStr(props.textDecoration) : parent.textDecoration;

    bool hasKerning = !props.kerning.empty();
    manualKerning = hasKerning || parent.manualKerning;

    kerning = hasKerning ? toAbsolute(props.kerning, scale, fontSize, 0) : parent.kerning;
    wordSpacing = !props.wordSpacing.empty() ? toAbsolute(props.wordSpacing, scale, fontSize, 0) : parent.wordSpacing;
    letterSpacing =
        !props.letterSpacing.empty() ? toAbsolute(props.letterSpacing, scale, fontSize, 0) : parent.letterSpacing;
}

const double FontData::DEFAULT_FONT_SIZE = vpToPx(12.0);
const double FontData::DEFAULT_KERNING = 0.0;
const double FontData::DEFAULT_WORD_SPACING = 0.0;
const double FontData::DEFAULT_LETTER_SPACING = 0.0;

const FontWeight FontData::WEIGHTS[] = {FontWeight::w100,   FontWeight::w200, FontWeight::w300,
                                        FontWeight::normal, FontWeight::w500, FontWeight::w600,
                                        FontWeight::bold,   FontWeight::w800, FontWeight::w900};

const int FontData::absoluteFontWeights[] = {400, 700, 100, 200, 300, 400, 500, 600, 700, 800, 900};

FontStyle fontStyleFromStr(const std::string &str) {
    if (str == "normal") {
        return FontStyle::normal;
    } else if (str == "italic") {
        return FontStyle::italic;
    } else if (str == "oblique") {
        return FontStyle::oblique;
    } else {
        // Default case
        return FontStyle::normal;
    }
}

FontWeight fontWeightFromStr(const std::string &str) {
    if (str == "w100") {
        return FontWeight::w100;
    } else if (str == "w200") {
        return FontWeight::w200;
    } else if (str == "w300") {
        return FontWeight::w300;
    } else if (str == "normal") {
        return FontWeight::normal;
    } else if (str == "w500") {
        return FontWeight::w500;
    } else if (str == "w600") {
        return FontWeight::w600;
    } else if (str == "bold") {
        return FontWeight::bold;
    } else if (str == "w800") {
        return FontWeight::w800;
    } else if (str == "w900") {
        return FontWeight::w900;
    } else if (str == "lighter") {
        return FontWeight::lighter;
    }
    return FontWeight::unknown;
}

TextAnchor textAnchorFromStr(const std::string &str) {
    if (str == "start") {
        return TextAnchor::start;
    } else if (str == "middle") {
        return TextAnchor::middle;
    } else if (str == "end") {
        return TextAnchor::end;
    } else {
        // Default case
        return TextAnchor::start;
    }
}

TextDecoration textDecorationFromStr(const std::string &str) {
    if (str == "None") {
        return TextDecoration::None;
    } else if (str == "Underline") {
        return TextDecoration::Underline;
    } else if (str == "Overline") {
        return TextDecoration::Overline;
    } else if (str == "LineThrough") {
        return TextDecoration::LineThrough;
    } else {
        // Default case
        return TextDecoration::None;
    }
}

FontVariantLigatures fontVariantFromStr(const std::string &str) {
    if (str == "normal") {
        return FontVariantLigatures::normal;
    } else if (str == "none") {
        return FontVariantLigatures::none;
    } else {
        // Default case
        return FontVariantLigatures::normal;
    }
}

} // namespace rnoh
