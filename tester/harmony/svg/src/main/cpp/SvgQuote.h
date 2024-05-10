#pragma once
#include "SvgNode.h"
#include <native_drawing/drawing_path.h>

namespace rnoh {

class SvgQuote : public SvgNode {
 public:
  SvgQuote() : SvgNode() {
    LOG(INFO) << "[SvgQuote] init";
    InitHrefFlag();
  }
  ~SvgQuote() override = default;

  OH_Drawing_Path* AsPath() override {
    LOG(INFO) << "[SvgQuote] AsPath";
    auto *path = OH_Drawing_PathCreate();
    for (const auto &child : children_) {
      auto *childPath = child->AsPath();
      //   path.Op(path, childPath, RSPathOp::UNION);
    }
//     return path;
  }

  void Draw(OH_Drawing_Canvas* canvas) override {
    // render composition on other svg tags
    LOG(INFO) << "[SvgQuote] Draw";
    OnDrawTraversedBefore(canvas);
    OnDrawTraversed(canvas);
    OnDrawTraversedAfter(canvas);
  }

 protected:
  virtual void OnDrawTraversedBefore(OH_Drawing_Canvas* canvas) {}
  virtual void OnDrawTraversedAfter(OH_Drawing_Canvas* canvas) {}

  // mask/pattern/filter/clipPath
  void InitHrefFlag() {
    hrefFill_ = true;
    hrefRender_ = false;
    passStyle_ = true;
    inheritStyle_ = false;
    drawTraversed_ = false;
  }
};

} // namespace rnoh
