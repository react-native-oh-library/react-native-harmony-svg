#pragma once

#include <string>
#include "SvgNode.h"
#include <native_drawing/drawing_path.h>

namespace rnoh {

class SvgDefs : public SvgNode {

public:
    SvgDefs() : SvgNode()
    {
        InitDefsFlag();
        LOG(INFO) << "[RNSvgDefsComponentInstance]: " ;
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
        auto* path = OH_Drawing_PathCreate();
        for (const auto& child : children_) {
            path = child->AsPath();
        //   path.Op(path, childPath, RSPathOp::UNION);
        }
        return path;
    }
};

}