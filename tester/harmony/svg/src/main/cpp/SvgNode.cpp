#include "SvgNode.h"
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_path.h>
#include <regex>
#include <string>
#include "properties/SvgDomType.h"
#include "utils/LinearMap.h"
#include "utils/StringUtils.h"
#include "utils/SvgAttributesParser.h"
#include "utils/Utils.h"

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
} // namespace

void SvgNode::SetAttr(const std::string& name, const std::string& value) {
  if (ParseAndSetSpecializedAttr(name, value)) {
    return;
  }
  static LinearMapNode<void (*)(const std::string&, SvgBaseAttribute&)> SVG_BASE_ATTRS[] = {
      //                 { DOM_SVG_SRC_CLIP_PATH,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         auto value = StringUtils::TrimStr(val);
      //                         if (value.find("url(") == 0) {
      //                             auto src = std::regex_replace(value,
      //                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"),
      //                                 "$1");
      //                             attrs.clipState.SetHref(src);
      //                         }
      //                     } },
      //                 { DOM_SVG_SRC_CLIP_RULE,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.clipState.SetClipRule(val);
      //                     } },
      //                 { DOM_CLIP_PATH,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         auto value = StringUtils::TrimStr(val);
      //                         if (value.find("url(") == 0) {
      //                             auto src = std::regex_replace(value,
      //                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"),
      //                                 "$1");
      //                             attrs.clipState.SetHref(src);
      //                         }
      //                     } },
      //                 { DOM_SVG_CLIP_RULE,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.clipState.SetClipRule(val);
      //                     } },
      //                 { DOM_SVG_FILL,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         auto value = StringUtils::TrimStr(val);
      //                         if (value.find("url(") == 0) {
      //                             auto src = std::regex_replace(value,
      //                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"),
      //                                 "$1");
      //                             attrs.fillState.SetHref(src);
      //                         } else {
      //                             Color fill = (val == VALUE_NONE ?
      //                             Color::TRANSPARENT :
      //                             SvgAttributesParser::GetColor(value));
      //                             attrs.fillState.SetColor(fill);
      //                         }
      //                     } },
      //                 { DOM_SVG_SRC_FILL_OPACITY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.fillState.SetOpacity(std::clamp(StringUtils::StringToDouble(val),
      //                         0.0, 1.0));
      //                     } },
      //                 { DOM_SVG_SRC_FILL_RULE,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.fillState.SetFillRule(val);
      //                     } },
      //                 { DOM_SVG_FILL_OPACITY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.fillState.SetOpacity(std::clamp(StringUtils::StringToDouble(val),
      //                         0.0, 1.0));
      //                     } },
      //                 { DOM_SVG_FILL_RULE,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.fillState.SetFillRule(val);
      //                     } },
      //                 { DOM_SVG_FILTER,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.filterId = val;
      //                     } },
      //                 { DOM_SVG_FONT_SIZE,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         Dimension fontSize =
      //                         StringUtils::StringToDimension(val);
      //                         if (GreatOrEqual(fontSize.Value(), 0.0)) {
      //                             attrs.textStyle.SetFontSize(fontSize);
      //                         }
      //                     } },
      //                 { DOM_SVG_HREF,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         auto value = StringUtils::TrimStr(val);
      //                         if (value.substr(0, 1) == "#") {
      //                             attrs.href = value.substr(1);
      //                         }
      //                     } },
      //                 { DOM_SVG_MASK,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.maskId = val;
      //                     } },
      //                 { DOM_SVG_OPACITY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.hasOpacity = true;
      //                         attrs.opacity =
      //                         std::clamp(StringUtils::StringToDouble(val),
      //                         0.0, 1.0);
      //                     } },
      //                 { DOM_SVG_PATTERN_TRANSFORM,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.transform = val;
      //                     } },
      //                 { DOM_SVG_STROKE,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         auto value = StringUtils::TrimStr(val);
      //                         if (value.find("url(") == 0) {
      //                             auto src = std::regex_replace(value,
      //                                 std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"),
      //                                 "$1");
      //                             attrs.strokeState.SetHref(src);
      //                         } else {
      //                             Color stroke = (val == VALUE_NONE ?
      //                             Color::TRANSPARENT :
      //                             SvgAttributesParser::GetColor(val));
      //                             attrs.strokeState.SetColor(stroke);
      //                         }
      //                     } },
      //                 { DOM_SVG_SRC_STROKE_DASHARRAY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         if (val.empty()) {
      //                             return;
      //                         }
      //                         std::vector<double> lineDashVector;
      //                         std::string handledStr =
      //                         StringUtils::ReplaceChar(val, ',', ' ');
      //                         StringUtils::StringSplitter(handledStr, '
      //                         ', lineDashVector);
      //                         attrs.strokeState.SetLineDash(lineDashVector);
      //                     } },
      //                 { DOM_SVG_SRC_STROKE_DASHOFFSET,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.strokeState.SetLineDashOffset(StringUtils::StringToDouble(val));
      //                     } },
      //                 { DOM_SVG_SRC_STROKE_LINECAP,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.strokeState.SetLineCap(SvgAttributesParser::GetLineCapStyle(val));
      //                     } },
      //                 { DOM_SVG_SRC_STROKE_LINEJOIN,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(val));
      //                     } },
      //                 { DOM_SVG_SRC_STROKE_MITERLIMIT,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         double miterLimit =
      //                         StringUtils::StringToDouble(val);
      //                         if (GreatOrEqual(miterLimit, 1.0)) {
      //                             attrs.strokeState.SetMiterLimit(miterLimit);
      //                         }
      //                     } },
      //                 { DOM_SVG_SRC_STROKE_OPACITY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.strokeState.SetOpacity(std::clamp(StringUtils::StringToDouble(val),
      //                         0.0, 1.0));
      //                     } },
      {DOM_SVG_STROKE_WIDTH,
       [](const std::string& val, SvgBaseAttribute& attrs) {
         Dimension lineWidth = StringUtils::StringToDimension(val, true);
         LOG(INFO) << "[SvgRect] setAtt: "
                   << attrs.strokeState.GetLineWidth().GetNativeValue(
                          DimensionUnit::PX);
         if (GreatOrEqual(lineWidth.Value(), 0.0)) {
           attrs.strokeState.SetLineWidth(lineWidth);
         }
       }},
      //                 { DOM_SVG_STROKE_DASHARRAY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         if (val.empty()) {
      //                             return;
      //                         }
      //                         std::vector<double> lineDashVector;
      //                         StringUtils::StringSplitter(val, ' ',
      //                         lineDashVector);
      //                         attrs.strokeState.SetLineDash(lineDashVector);
      //                     } },

      //         In props, strokeDashoffset is Float type, it might need
      //         another way to deal with
      //         {DOM_SVG_STROKE_DASHOFFSET,
      //          [](const std::string &val, SvgBaseAttribute &attrs) {
      //              attrs.strokeState.SetLineDashOffset(StringUtils::StringToDouble(val));
      //          }},
      {DOM_SVG_STROKE_LINECAP,
       [](const std::string& val, SvgBaseAttribute& attrs) {
         attrs.strokeState.SetLineCap(
             SvgAttributesParser::GetLineCapStyle(val));
       }},
      //         { DOM_SVG_STROKE_LINEJOIN,
      //             [](const std::string& val, SvgBaseAttribute& attrs) {
      //                 attrs.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(val));
      //             } },
      //         { DOM_SVG_STROKE_MITERLIMIT,
      //             [](const std::string& val, SvgBaseAttribute& attrs) {
      //                 double miterLimit =
      //                 StringUtils::StringToDouble(val);
      //                 if (GreatOrEqual(miterLimit, 1.0)) {
      //                     attrs.strokeState.SetMiterLimit(miterLimit);
      //                 }
      //             } },
      //                 { DOM_SVG_STROKE_OPACITY,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.strokeState.SetOpacity(std::clamp(StringUtils::StringToDouble(val),
      //                         0.0, 1.0));
      //                     } },
      //                 { DOM_SVG_STROKE_WIDTH,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         Dimension lineWidth =
      //                         StringUtils::StringToDimension(val);
      //                         if (GreatOrEqual(lineWidth.Value(), 0.0)) {
      //                             attrs.strokeState.SetLineWidth(lineWidth);
      //                         }
      //                     } },
      //                 { DOM_TRANSFORM,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.transform = val;
      //                     } },
      //                 { DOM_SVG_SRC_TRANSFORM_ORIGIN,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         attrs.transformOrigin = val;
      //                     } },
      //                 { DOM_SVG_XLINK_HREF,
      //                     [](const std::string& val, SvgBaseAttribute&
      //                     attrs) {
      //                         auto value = StringUtils::TrimStr(val);
      //                         if (value.substr(0, 1) == "#") {
      //                             attrs.href = value.substr(1);
      //                         }
      //                     } }
  };

  //         auto compareNodes = [](const LinearMapNode<void (*)(const
  //         std::string&, SvgBaseAttribute&)>& a,
  //                            const LinearMapNode<void (*)(const std::string&,
  //                            SvgBaseAttribute&)>& b) {
  //         return a.key > b.key;
  //     };

  // 对 SVG_BASE_ATTRS 数组进行排序
  //     std::sort(std::begin(SVG_BASE_ATTRS), std::end(SVG_BASE_ATTRS),
  //     compareNodes);
  auto attrIter = BinarySearchFindIndex(
      SVG_BASE_ATTRS, ArraySize(SVG_BASE_ATTRS), name.c_str());
  LOG(INFO) << "[SvgRect] attrIter: " << attrIter;
  LOG(INFO) << "[SvgRect] ArraySize(SVG_BASE_ATTRS): "
            << ArraySize(SVG_BASE_ATTRS);
  LOG(INFO) << "[SvgRect] name.c_str(): " << name.c_str();
  if (attrIter != -1) {
    SVG_BASE_ATTRS[attrIter].value(value, attributes_);
  }
}

void SvgNode::InitStyle(const SvgBaseAttribute& attr) {
  InheritAttr(attr);
  if (hrefFill_) {
    // auto href = attributes_.fillState.GetHref();
    // if (!href.empty()) {
    //   auto gradient = GetGradient(href);
    //   if (gradient) {
    //     attributes_.fillState.SetGradient(gradient.value());
    //   }
    // }
  }
  if (hrefRender_) {
    // hrefClipPath_ = attributes_.clipState.GetHref();
    // opacity_ = OpacityDoubleToUint8(attributes_.opacity);
    // transform_ = attributes_.transform;
    // hrefMaskId_ = ParseIdFromUrl(attributes_.maskId);
  }
  OnInitStyle();
  if (passStyle_) {
    for (auto& node : children_) {
      // pass down style only if child inheritStyle_ is true
      node->InitStyle((node->inheritStyle_) ? attributes_ : SvgBaseAttribute());
    }
  }
}

void SvgNode::OnDrawTraversed(OH_Drawing_Canvas* canvas) {
  auto smoothEdge = GetSmoothEdge();
  for (auto& node : children_) {
    if (node && node->drawTraversed_) {
      if (GreatNotEqual(smoothEdge, 0.0f)) {
        node->SetSmoothEdge(smoothEdge);
      }
      node->Draw(canvas);
    }
  }
}

void SvgNode::OnClipPath(OH_Drawing_Canvas* canvas) {
  auto refSvgNode = context_->GetSvgNodeById(hrefClipPath_);
  if (!refSvgNode) {
    return;
  };
  auto* clipPath = refSvgNode->AsPath();
  OH_Drawing_CanvasClipPath(
      canvas, clipPath, OH_Drawing_CanvasClipOp::INTERSECT, true);
  OH_Drawing_PathDestroy(clipPath);
}

void SvgNode::OnMask(OH_Drawing_Canvas* canvas) {
  auto refMask = context_->GetSvgNodeById(hrefMaskId_);
  if (!refMask) {
    return;
  };
  refMask->Draw(canvas);
}

void SvgNode::OnTransform(OH_Drawing_Canvas* canvas) {
  auto* matrix = OH_Drawing_MatrixCreate();
  OH_Drawing_MatrixSetMatrix(
      matrix,
      transform_[0],
      transform_[1],
      transform_[2],
      transform_[3],
      transform_[4],
      transform_[5],
      transform_[6],
      transform_[7],
      transform_[8]);
  OH_Drawing_CanvasConcatMatrix(canvas, matrix);
  OH_Drawing_MatrixDestroy(matrix);
}

double SvgNode::ConvertDimensionToPx(
    const Dimension& value,
    const Size& viewPort,
    SvgLengthType type) const {
  switch (value.Unit()) {
    case DimensionUnit::PERCENT: {
      if (type == SvgLengthType::HORIZONTAL) {
        return value.Value() * viewPort.Width();
      }
      if (type == SvgLengthType::VERTICAL) {
        return value.Value() * viewPort.Height();
      }
      if (type == SvgLengthType::OTHER) {
        return value.Value() * sqrt(viewPort.Width() * viewPort.Height());
      }
      return 0.0;
    }
    case DimensionUnit::PX:
      return value.Value();
    case DimensionUnit::VP:
      return vpToPx(value.Value());
    default:
      return vpToPx(value.Value());
  }
}

void SvgNode::Draw(OH_Drawing_Canvas* canvas) {
  // mask and filter create extra layers, need to record initial layer count
  const auto count = OH_Drawing_CanvasGetSaveCount(canvas);
  OH_Drawing_CanvasSave(canvas);
  if (!hrefClipPath_.empty()) {
    OnClipPath(canvas);
  }
  if (!transform_.empty()) {
    OnTransform(canvas);
  }
  if (!hrefMaskId_.empty()) {
    OnMask(canvas);
  }

  OnDraw(canvas);
  OnDrawTraversed(canvas);
  OH_Drawing_CanvasRestoreToCount(canvas, count);
};
} // namespace rnoh