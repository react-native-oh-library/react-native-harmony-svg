#pragma once
#include "SvgNode.h"

namespace rnoh {

class SvgGroup : public SvgNode {
    
public:
    SvgGroup() : SvgNode()
    {
        InitGroupFlag();
    }
    ~SvgGroup() override = default;

protected:
    // svg g use
    void InitGroupFlag()
    {
//         hrefFill_ = true;
//         hrefRender_ = true;
//         passStyle_ = true;
//         inheritStyle_ = true;
//         drawTraversed_ = true;
    }
};

} // namespace rnoh
