#pragma once
#include "SvgNode.h"
#include <native_drawing/drawing_path.h>

namespace rnoh {

class SvgQuote : public SvgNode {
 public:
  SvgQuote() : SvgNode() {
    InitHrefFlag();
  }
  ~SvgQuote() override = default;

  OH_Drawing_Path *getClipPath(OH_Drawing_Path *path) {
      LOG(INFO) << "[SvgQuote] getClipPath";
      for (const auto &child : children_) {
          auto *childPath = child->AsPath();
          OH_Drawing_PathAddPath(path, childPath, nullptr);
      }
      return path;
  }

  OH_Drawing_Path *getClipPath(OH_Drawing_Path *path, OH_Drawing_PathOpMode op) {
      LOG(INFO) << "[SvgQuote] getClipPath with op, op = " << op;
      for (const auto &child : children_) {
          auto *childPath = child->AsPath();
          OH_Drawing_PathOp(path, childPath, op);
      }
      return path;
  }

  OH_Drawing_Path* AsPath() override {
    LOG(INFO) << "[SvgQuote] AsPath";
    auto *path = OH_Drawing_PathCreate();

    if (attributes_.clipState.IsEvenodd()) {
        return getClipPath(path);
    } else {
        return getClipPath(path, OH_Drawing_PathOpMode::PATH_OP_MODE_UNION );
    }
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
