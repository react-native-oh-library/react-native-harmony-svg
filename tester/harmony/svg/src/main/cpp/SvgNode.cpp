#include <regex>
#include <string>
#include "SvgNode.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"
#include "utils/SvgAttributesParser.h"
#include "properties/SvgDomType.h"

namespace rnoh {
namespace {
constexpr size_t SVG_ATTR_ID_FLAG_NUMS = 6;
const char VALUE_NONE[] = "none";
const char ATTR_NAME_OPACITY[] = "opacity";
const char DOM_SVG_SRC_FILL_OPACITY[] = "fill-opacity";
const char DOM_SVG_SRC_FILL_RULE[] = "fill-rule";
const char DOM_SVG_SRC_STROKE_DASHARRAY[] = "stroke-dasharray";
const char DOM_SVG_SRC_STROKE_DASHOFFSET[] = "stroke-dashoffset";
const char DOM_SVG_SRC_STROKE_LINECAP[] = "stroke-linecap";
const char DOM_SVG_SRC_STROKE_LINEJOIN[] = "stroke-linejoin";
const char DOM_SVG_SRC_STROKE_MITERLIMIT[] = "stroke-miterlimit";
const char DOM_SVG_SRC_STROKE_OPACITY[] = "stroke-opacity";
const char DOM_SVG_SRC_STROKE_WIDTH[] = "stroke-width";
const char DOM_SVG_SRC_CLIP_PATH[] = "clip-path";
const char DOM_SVG_SRC_CLIP_RULE[] = "clip-rule";
const char DOM_SVG_SRC_TRANSFORM_ORIGIN[] = "transform-origin";
}

void SvgNode::SetAttr(const std::string& name, const std::string& value)
{
    if (ParseAndSetSpecializedAttr(name, value)) {
        return;
    }
    static LinearMapNode<void (*)(const std::string &, SvgBaseAttribute &)> SVG_BASE_ATTRS[] = {
//                 { DOM_SVG_SRC_CLIP_PATH,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         auto value = StringUtils::TrimStr(val);
//                         if (value.find("url(") == 0) {
//                             auto src = std::regex_replace(value,
//                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
//                             attrs.clipState.SetHref(src);
//                         }
//                     } },
//                 { DOM_SVG_SRC_CLIP_RULE,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.clipState.SetClipRule(val);
//                     } },
//                 { DOM_CLIP_PATH,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         auto value = StringUtils::TrimStr(val);
//                         if (value.find("url(") == 0) {
//                             auto src = std::regex_replace(value,
//                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
//                             attrs.clipState.SetHref(src);
//                         }
//                     } },
//                 { DOM_SVG_CLIP_RULE,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.clipState.SetClipRule(val);
//                     } },
//                 { DOM_SVG_FILL,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         auto value = StringUtils::TrimStr(val);
//                         if (value.find("url(") == 0) {
//                             auto src = std::regex_replace(value,
//                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
//                             attrs.fillState.SetHref(src);
//                         } else {
//                             Color fill = (val == VALUE_NONE ? Color::TRANSPARENT :
//                             SvgAttributesParser::GetColor(value));
//                             attrs.fillState.SetColor(fill);
//                         }
//                     } },
//                 { DOM_SVG_SRC_FILL_OPACITY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.fillState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
//                     } },
//                 { DOM_SVG_SRC_FILL_RULE,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.fillState.SetFillRule(val);
//                     } },
//                 { DOM_SVG_FILL_OPACITY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.fillState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
//                     } },
//                 { DOM_SVG_FILL_RULE,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.fillState.SetFillRule(val);
//                     } },
//                 { DOM_SVG_FILTER,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.filterId = val;
//                     } },
//                 { DOM_SVG_FONT_SIZE,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         Dimension fontSize = StringUtils::StringToDimension(val);
//                         if (GreatOrEqual(fontSize.Value(), 0.0)) {
//                             attrs.textStyle.SetFontSize(fontSize);
//                         }
//                     } },
//                 { DOM_SVG_HREF,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         auto value = StringUtils::TrimStr(val);
//                         if (value.substr(0, 1) == "#") {
//                             attrs.href = value.substr(1);
//                         }
//                     } },
//                 { DOM_SVG_MASK,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.maskId = val;
//                     } },
//                 { DOM_SVG_OPACITY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.hasOpacity = true;
//                         attrs.opacity = std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0);
//                     } },
//                 { DOM_SVG_PATTERN_TRANSFORM,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.transform = val;
//                     } },
//                 { DOM_SVG_STROKE,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         auto value = StringUtils::TrimStr(val);
//                         if (value.find("url(") == 0) {
//                             auto src = std::regex_replace(value,
//                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
//                             attrs.strokeState.SetHref(src);
//                         } else {
//                             Color stroke = (val == VALUE_NONE ? Color::TRANSPARENT :
//                             SvgAttributesParser::GetColor(val));
//                             attrs.strokeState.SetColor(stroke);
//                         }
//                     } },
//                 { DOM_SVG_SRC_STROKE_DASHARRAY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         if (val.empty()) {
//                             return;
//                         }
//                         std::vector<double> lineDashVector;
//                         std::string handledStr = StringUtils::ReplaceChar(val, ',', ' ');
//                         StringUtils::StringSplitter(handledStr, ' ', lineDashVector);
//                         attrs.strokeState.SetLineDash(lineDashVector);
//                     } },
//                 { DOM_SVG_SRC_STROKE_DASHOFFSET,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.strokeState.SetLineDashOffset(StringUtils::StringToDouble(val));
//                     } },
//                 { DOM_SVG_SRC_STROKE_LINECAP,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.strokeState.SetLineCap(SvgAttributesParser::GetLineCapStyle(val));
//                     } },
//                 { DOM_SVG_SRC_STROKE_LINEJOIN,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(val));
//                     } },
//                 { DOM_SVG_SRC_STROKE_MITERLIMIT,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         double miterLimit = StringUtils::StringToDouble(val);
//                         if (GreatOrEqual(miterLimit, 1.0)) {
//                             attrs.strokeState.SetMiterLimit(miterLimit);
//                         }
//                     } },
//                 { DOM_SVG_SRC_STROKE_OPACITY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.strokeState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
//                     } },
        {DOM_SVG_STROKE_WIDTH,
         [](const std::string &val, SvgBaseAttribute &attrs) {
             Dimension lineWidth = StringUtils::StringToDimension(val, true);
             LOG(INFO) << "[SvgRect] setAtt: " << attrs.strokeState.GetLineWidth().GetNativeValue(DimensionUnit::PX);
             if (GreatOrEqual(lineWidth.Value(), 0.0)) {
                 attrs.strokeState.SetLineWidth(lineWidth);
             }
         }},
//                 { DOM_SVG_STROKE_DASHARRAY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         if (val.empty()) {
//                             return;
//                         }
//                         std::vector<double> lineDashVector;
//                         StringUtils::StringSplitter(val, ' ', lineDashVector);
//                         attrs.strokeState.SetLineDash(lineDashVector);
//                     } },
        
//         In props, strokeDashoffset is Float type, it might need another way to deal with
//         {DOM_SVG_STROKE_DASHOFFSET,
//          [](const std::string &val, SvgBaseAttribute &attrs) {
//              attrs.strokeState.SetLineDashOffset(StringUtils::StringToDouble(val));
//          }},
        { DOM_SVG_STROKE_LINECAP,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineCap(SvgAttributesParser::GetLineCapStyle(val));
            } },
//         { DOM_SVG_STROKE_LINEJOIN,
//             [](const std::string& val, SvgBaseAttribute& attrs) {
//                 attrs.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(val));
//             } },
//         { DOM_SVG_STROKE_MITERLIMIT,
//             [](const std::string& val, SvgBaseAttribute& attrs) {
//                 double miterLimit = StringUtils::StringToDouble(val);
//                 if (GreatOrEqual(miterLimit, 1.0)) {
//                     attrs.strokeState.SetMiterLimit(miterLimit);
//                 }
//             } },
//                 { DOM_SVG_STROKE_OPACITY,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.strokeState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
//                     } },
//                 { DOM_SVG_STROKE_WIDTH,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         Dimension lineWidth = StringUtils::StringToDimension(val);
//                         if (GreatOrEqual(lineWidth.Value(), 0.0)) {
//                             attrs.strokeState.SetLineWidth(lineWidth);
//                         }
//                     } },
//                 { DOM_TRANSFORM,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.transform = val;
//                     } },
//                 { DOM_SVG_SRC_TRANSFORM_ORIGIN,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         attrs.transformOrigin = val;
//                     } },
//                 { DOM_SVG_XLINK_HREF,
//                     [](const std::string& val, SvgBaseAttribute& attrs) {
//                         auto value = StringUtils::TrimStr(val);
//                         if (value.substr(0, 1) == "#") {
//                             attrs.href = value.substr(1);
//                         }
//                     } }
    };
    
//         auto compareNodes = [](const LinearMapNode<void (*)(const std::string&, SvgBaseAttribute&)>& a, 
//                            const LinearMapNode<void (*)(const std::string&, SvgBaseAttribute&)>& b) {
//         return a.key > b.key;
//     };

    // 对 SVG_BASE_ATTRS 数组进行排序
//     std::sort(std::begin(SVG_BASE_ATTRS), std::end(SVG_BASE_ATTRS), compareNodes);
    auto attrIter = BinarySearchFindIndex(SVG_BASE_ATTRS, ArraySize(SVG_BASE_ATTRS), name.c_str());
    LOG(INFO) << "[SvgRect] attrIter: " << attrIter;
    LOG(INFO) << "[SvgRect] ArraySize(SVG_BASE_ATTRS): " << ArraySize(SVG_BASE_ATTRS);
    LOG(INFO) << "[SvgRect] name.c_str(): " << name.c_str();
    if (attrIter != -1) {
        SVG_BASE_ATTRS[attrIter].value(value, attributes_);
    }
}
}