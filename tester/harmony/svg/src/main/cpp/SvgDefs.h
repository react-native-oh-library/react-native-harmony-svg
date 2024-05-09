#pragma once

#include "SvgNode.h"
#include "SvgGraphic.h"

namespace rnoh {

class SvgDefs : public SvgNode {
public:
    SvgDefs() : SvgNode()
    {
        InitDefsFlag();
    }

    ~SvgDefs() override = default;

    // static RefPtr<SvgNode> Create()
    // {
    //     return AceType::MakeRefPtr<SvgDefs>();
    // }

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
            // path.Op(path, childPath, RSPathOp::UNION);
            path = childPath;
        }
        return path;
    }
};

} // namespace rnoh