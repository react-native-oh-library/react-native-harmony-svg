#pragma once

#include <string>
#include "SvgNode.h"
#include "SvgGraphic.h"

namespace rnoh {
namespace svg {

class SvgDefs : public SvgNode {

public:
    SvgDefs() : SvgNode() { InitNoneFlag(); }

    ~SvgDefs() override = default;

    drawing::Path AsPath() override {
        drawing::Path path;
        LOG(INFO) << "[SvgDfes:AsPath] : arrived Defs AsPath";
        for (auto child : children_) {
            if (!child) {
                LOG(INFO) << "[SvgDfes:AsPath] : childnode is a null ptr";
            } else {
                LOG(INFO) << "[SvgDfes:AsPath] : get child path:";
            }
            auto childPath = child->AsPath();
            path.Union(childPath);
        }
        return path;
    }
};

} // namespace svg
} // namespace rnoh
