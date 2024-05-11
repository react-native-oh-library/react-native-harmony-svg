
#include "SvgNode.h"

namespace rnoh {
std::shared_ptr<SvgNode> SvgContext::GetSvgNodeById(const std::string &id) const {
    auto item = idMapper_.find(id);
    if (item != idMapper_.end()) {
        return item->second;
    }
    return nullptr;
}

void SvgContext::PushStyle(const std::string &styleName, const std::pair<std::string, std::string> &attrPair) {
    const auto &arrMapIter = styleMap_.find(styleName);
    if (arrMapIter == styleMap_.end()) {
        AttrMap attrMap;
        attrMap.emplace(attrPair);
        styleMap_.emplace(std::make_pair(styleName, attrMap));
    } else {
        if (arrMapIter->second.find(attrPair.first) != arrMapIter->second.end()) {
            arrMapIter->second.erase(attrPair.first);
        }
        arrMapIter->second.emplace(attrPair);
    }
}

const AttrMap &SvgContext::GetAttrMap(const std::string &key) const {
    auto styleClassIter = styleMap_.find(key);
    if (styleClassIter != styleMap_.end()) {
        return styleClassIter->second;
    }
    static AttrMap emptyMap;
    return emptyMap;
}

const Rect &SvgContext::GetRootViewBox() const {
    if (!rootViewBox_.IsValid()) {
        static Rect rect;
        rect = Rect(0, 0, svgSize_.Width(), svgSize_.Height());
        return rect;
    }
    return rootViewBox_;
}
} // namespace rnoh
