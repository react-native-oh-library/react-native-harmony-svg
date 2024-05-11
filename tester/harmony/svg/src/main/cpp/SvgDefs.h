#pragma once

#include <string>
#include "SvgNode.h"
#include <native_drawing/drawing_path.h>
#include "SvgGraphic.h"

namespace rnoh {

class SvgDefs : public SvgNode {

public:
    SvgDefs() : SvgNode()
    {
        InitDefsFlag();

    }

    ~SvgDefs() override = default;

    void InitDefsFlag()
    {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    OH_Drawing_Path *AsPath() override
    {
        auto path = OH_Drawing_PathCreate();
        LOG(INFO) << "[SvgDfes:AsPath] : arrived Defs AsPath";
        for (auto child : children_) {
            if(!child) {
                LOG(INFO) << "[SvgDfes:AsPath] : childnode is a null ptr" ;
            } else {
                LOG(INFO) << "[SvgDfes:AsPath] : get child path:" ;
            }
            auto childPath = child->AsPath();
            OH_Drawing_PathOp(path, childPath, PATH_OP_MODE_UNION);
        }
        return path;
    }
};

} // namespace rnoh
