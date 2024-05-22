//
// Created on 2024/5/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGVIEWMANAGER_H
#define HARMONY_SVGVIEWMANAGER_H

#include "SvgSvg.h"
#include <map>
#include <memory>

namespace rnoh {
namespace svg {

class SvgViewManager {
public:
    static SvgViewManager &getInstance() {
        static SvgViewManager instance;
        return instance;
    }

    void setSvgView(int tag, std::shared_ptr<SvgSvg> svg);

    std::shared_ptr<SvgSvg> getSvgViewByTag(int tag);
    
    void onDropView(int tag);
    
private:
    SvgViewManager() {}

    SvgViewManager(const SvgViewManager &) = delete;
    SvgViewManager &operator=(const SvgViewManager &) = delete;

    std::map<int, std::shared_ptr<SvgSvg>> tagToSvgViewMap;
};

}
}

#endif //HARMONY_SVGVIEWMANAGER_H
