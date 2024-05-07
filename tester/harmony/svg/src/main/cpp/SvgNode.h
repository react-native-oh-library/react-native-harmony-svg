// from ArkUI "frameworks/core/components_ng/svg/parse/svg_node.h"
#pragma once

#include <glog/logging.h>
#include <native_drawing/drawing_canvas.h>
#include <memory>
#include <vector>
#include "SvgBaseAttribute.h"
#include "SvgContext.h"
#include "properties/Dimension.h"
#include "properties/Size.h"

namespace rnoh {

enum class SvgLengthType {
  HORIZONTAL,
  VERTICAL,
  OTHER,
};

class SvgNode {
 public:
  SvgNode() = default;
  virtual ~SvgNode() = default;

  std::shared_ptr<SvgContext> GetContext() {
    return context_;
  }
  void SetContext(std::shared_ptr<SvgContext> context) {
    context_ = context;
  }

  void InitStyle(const SvgBaseAttribute& attr);

  virtual void Draw(OH_Drawing_Canvas* canvas);

  virtual void SetAttr(const std::string& name, const std::string& value);

  virtual bool ParseAndSetSpecializedAttr(
      const std::string& name,
      const std::string& value) {
    return false;
  }

  virtual OH_Drawing_Path* AsPath() const {
    LOG(INFO) << "[SVGNode] AsPath";
  };

  virtual void AppendChild(const std::shared_ptr<SvgNode>& child) {
    children_.emplace_back(child);
  }

 protected:
  virtual void InheritAttr(const SvgBaseAttribute& parent) {
    attributes_.Inherit(parent);
  }

  void InheritUseAttr(const SvgBaseAttribute& parent) {
    attributes_.InheritFromUse(parent);
  }

  // override as need by derived class
  // called by function AppendChild
  virtual void OnAppendChild(const std::shared_ptr<SvgNode>& child) {}
  // called by function InitStyle
  virtual void OnInitStyle() {}

  virtual void OnDraw(OH_Drawing_Canvas* canvas) {}
  virtual void OnDrawTraversed(OH_Drawing_Canvas* canvas);
  void OnClipPath(OH_Drawing_Canvas* canvas);
  void OnMask(OH_Drawing_Canvas* canvas);
  void OnTransform(OH_Drawing_Canvas* canvas);

  void SetSmoothEdge(float edge) {
    smoothEdge_ = edge;
  }
  float GetSmoothEdge() const {
    return smoothEdge_;
  }

  double ConvertDimensionToPx(
      const Dimension& value,
      const Size& viewPort,
      SvgLengthType type) const;

  SvgBaseAttribute attributes_;
  std::shared_ptr<SvgContext> context_;

  std::vector<std::shared_ptr<SvgNode>> children_;
  std::string nodeId_;
  std::vector<float> transform_; // transform matrix

  std::string hrefClipPath_;
  std::string hrefMaskId_;
  std::string imagePath_;
  float smoothEdge_ = 0.0f;
  uint8_t opacity_ = 0xFF;

  bool hrefFill_ = true; // get fill attributes from reference
  bool hrefRender_ = true; // get render attr (mask, filter, transform, opacity,
                           // clip path) from reference
  bool passStyle_ = true; // pass style attributes to child node, TAGS
                          // circle/path/line/... = false
  bool inheritStyle_ = true; // inherit style attributes from parent node, TAGS
                             // mask/defs/pattern/filter = false
  bool drawTraversed_ =
      true; // enable OnDraw, TAGS mask/defs/pattern/filter = false
};

} // namespace rnoh
