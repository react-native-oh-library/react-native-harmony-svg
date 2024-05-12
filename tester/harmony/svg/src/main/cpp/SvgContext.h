#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "properties/Rect.h"
#include "properties/Size.h"

namespace rnoh {
using AttrMap = std::unordered_map<std::string, std::string>;
using ClassStyleMap = std::unordered_map<std::string, AttrMap>;
class SvgNode;
class SvgContext {
public:
    void Push(const std::string &value, const std::shared_ptr<SvgNode> &svgNode) { idMapper_.emplace(value, svgNode); }

    std::shared_ptr<SvgNode> GetSvgNodeById(const std::string &id) const;

    void PushStyle(const std::string &styleName, const std::pair<std::string, std::string> &attrPair);

    const AttrMap &GetAttrMap(const std::string &key) const;

    void SetRootViewBox(const Rect &viewBox) { rootViewBox_ = viewBox; }

    const Rect &GetRootViewBox() const;

    void SetSvgSize(const Size &size) { svgSize_ = size; }
    const Size &GetSvgSize() const { return svgSize_; }

private:
    std::unordered_map<std::string, std::weak_ptr<SvgNode>> idMapper_;
    ClassStyleMap styleMap_;
    Rect rootViewBox_;
    Size svgSize_;
};
} // namespace rnoh