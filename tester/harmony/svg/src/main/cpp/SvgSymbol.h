#pragma once

#include <string>
#include "SvgNode.h"
#include "properties/Rect.h"

namespace rnoh {

class SvgSymbol : public SvgNode {

public:
    std::string id;
    Rect viewBox;

    SvgSymbol() : SvgNode()
    {
        InitDefsFlag();
        
    }

    ~SvgSymbol() override = default;

    void InitDefsFlag()
    {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    OH_Drawing_Path *AsPath() override
    {
        OH_Drawing_Path *path;
        for (auto child : children_) {
            path = child->AsPath();
        }
        return path;
    }
};

}