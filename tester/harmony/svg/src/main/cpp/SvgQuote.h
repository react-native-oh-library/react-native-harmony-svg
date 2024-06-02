#pragma once
#include "SvgNode.h"
#include <native_drawing/drawing_path.h>

namespace rnoh {
namespace svg {

class SvgQuote : public SvgNode {
public:
    SvgQuote() : SvgNode() { InitHrefFlag(); }
    ~SvgQuote() override = default;

    drawing::Path getClipPath(drawing::Path path) {
        DLOG(INFO) << "[SvgQuote] getClipPath";
        for (const auto &child : children_) {
            auto childPath = child->AsPath();
            path.AddPath(childPath);
        }
        return path;
    }

    drawing::Path getClipPath(drawing::Path path, drawing::Path::OpMode op) {
        DLOG(INFO) << "[SvgQuote] getClipPath with op, op = " << op;
        for (const auto &child : children_) {
            auto childPath = child->AsPath();
            path.Op(childPath, op);
        }
        return path;
    }

    drawing::Path AsPath() override {
        DLOG(INFO) << "[SvgQuote] AsPath";
        drawing::Path path;

        if (attributes_.clipState.IsEvenodd()) {
            return getClipPath(path);
        } else {
            return getClipPath(path, drawing::Path::OpMode::PATH_OP_MODE_UNION);
        }
    }

    void Draw(OH_Drawing_Canvas *canvas) override {
        // render composition on other svg tags
        DLOG(INFO) << "[SvgQuote] Draw";
        OnDrawTraversedBefore(canvas);
        OnDrawTraversed(canvas);
        OnDrawTraversedAfter(canvas);
    }

protected:
    virtual void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) {}
    virtual void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) {}

    // mask/pattern/filter/clipPath
    void InitHrefFlag() {
        hrefFill_ = true;
        hrefRender_ = false;
        passStyle_ = true;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }
};

} // namespace svg
} // namespace rnoh
