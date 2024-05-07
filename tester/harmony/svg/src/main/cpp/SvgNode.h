// from ArkUI "frameworks/core/components_ng/svg/parse/svg_node.h"
#pragma once

#include <vector>
#include <native_drawing/drawing_canvas.h>
#include "properties/Dimension.h"
#include "properties/Size.h"
#include <glog/logging.h>
#include "SvgBaseAttribute.h"

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

    virtual void Draw(OH_Drawing_Canvas *canvas) {
        for (const auto &child : children_) {
            if (child != nullptr) {
                child->Draw(canvas);
            }
        }
        OnDraw(canvas);
    };

    virtual void SetAttr(const std::string &name, const std::string &value);

    virtual bool ParseAndSetSpecializedAttr(const std::string &name, const std::string &value) { return false; }

    virtual OH_Drawing_Path *AsPath() {
        LOG(INFO) << "[SVGNode] AsPath";
        return nullptr;
    };


    virtual void OnDraw(OH_Drawing_Canvas *canvas) {}

    virtual void AppendChild(const std::shared_ptr<SvgNode> &child) { children_.emplace_back(child); }

    std::vector<std::shared_ptr<SvgNode>> children_;

protected:
    SvgBaseAttribute attributes_;

    float smoothEdge_ = 0.0f;
    uint8_t opacity_ = 0xFF;
    float GetSmoothEdge() const { return smoothEdge_; }
    
//     std::optional<ImageColorFilter> GetColorFilter() const { return colorFilter_; }

    bool hrefFill_ = true;      // get fill attributes from reference
    bool hrefRender_ = true;    // get render attr (mask, filter, transform, opacity, clip path) from reference
    bool passStyle_ = true;     // pass style attributes to child node, TAGS circle/path/line/... = false
    bool inheritStyle_ = true;  // inherit style attributes from parent node, TAGS mask/defs/pattern/filter = false
    bool drawTraversed_ = true; // enable OnDraw, TAGS mask/defs/pattern/filter = false

    double ConvertDimensionToPx(const Dimension &value, const Size &viewPort, SvgLengthType type) const {
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
};

class SvgHost {
public:
    void SetSvgNode(const std::shared_ptr<SvgNode> &svgNode) { m_svgNode = svgNode; };
    const std::shared_ptr<SvgNode> &GetSvgNode() { return m_svgNode; };

private:
    std::shared_ptr<SvgNode> m_svgNode;
};

} // namespace rnoh
