#include "TextStyle.h"
#include <glog/logging.h>

namespace rnoh::drawing {
static std::vector<std::string> disableDiscretionaryLigatures = {"liga", "clig", "dlig", "hlig", "cala"};
static std::vector<std::string> defaultFeatures = {"rlig", "liga", "clig", "calt", "locl",
                                                   "ccmp", "mark", "mkmk", "kern"};
static std::vector<std::string> additionalLigatures = {"hlig", "cala"};
static std::string fontWeightTag = "wght";

TextStyle::TextStyle() : textStyle_(UniqueTextStyle(OH_Drawing_CreateTextStyle(), OH_Drawing_DestroyTextStyle)) {}

void TextStyle::Update(const std::shared_ptr<svg::FontData> &style) {
    auto *ts = textStyle_.get();
    OH_Drawing_SetTextStyleFontSize(ts, style->fontSize);
    OH_Drawing_SetTextStyleFontWeight(ts, static_cast<int>(style->fontWeight));
    OH_Drawing_SetTextStyleFontStyle(ts, static_cast<int>(style->fontStyle));
    if (!style->fontFamily.empty()) {
        std::vector<const char *> ff{style->fontFamily.c_str()};
        OH_Drawing_SetTextStyleFontFamilies(ts, 1, ff.data());
    }
    OH_Drawing_SetTextStyleDecoration(ts, static_cast<int>(style->textDecoration));
    OH_Drawing_SetTextStyleLetterSpacing(ts, style->letterSpacing);
    OH_Drawing_SetTextStyleWordSpacing(ts, style->wordSpacing);

    for (const auto &key : defaultFeatures) {
        OH_Drawing_TextStyleAddFontFeature(ts, key.c_str(), 1);
    }
    OH_Drawing_TextStyleAddFontFeature(ts, style->fontFeatureSettings.c_str(), 1);

    const bool allowOptionalLigatures =
        style->letterSpacing == 0 && style->fontVariantLigatures == svg::FontVariantLigatures::normal;
    if (allowOptionalLigatures) {
        for (const auto &key : additionalLigatures) {
            OH_Drawing_TextStyleAddFontFeature(ts, key.c_str(), 1);
        }
    } else {
        for (const auto &key : disableDiscretionaryLigatures) {
            OH_Drawing_TextStyleAddFontFeature(ts, key.c_str(), 0);
        }
    }
}

} // namespace rnoh::drawing