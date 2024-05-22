//
// Created on 2024/5/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SvgViewManager.h"
#include <utility>

namespace rnoh {
namespace svg {

void SvgViewManager::setSvgView(int tag, std::shared_ptr<SvgSvg> svg) {
    tagToSvgViewMap.insert(std::make_pair(tag, svg));
//     for (const auto &pair : tagToSvgViewMap) {
//         int key = pair.first;
//         LOG(INFO) << "liwang----->[SvgViewManager] key=" << key;
//     }
};

std::shared_ptr<SvgSvg> SvgViewManager::getSvgViewByTag(int tag){
    std::shared_ptr<SvgSvg> value;
    auto it = tagToSvgViewMap.find(tag);
    if (it != tagToSvgViewMap.end()) {
        value = it->second;
    }
    return value;
}

void SvgViewManager::onDropView(int tag) {
    auto it = tagToSvgViewMap.find(tag);
    if (it != tagToSvgViewMap.end()) {
        tagToSvgViewMap.erase(tag);
    }
};

}
}