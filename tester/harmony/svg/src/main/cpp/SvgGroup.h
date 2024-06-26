#pragma once
#include "SvgNode.h"
#include "properties/Font.h"
#include "FontHolderBase.h"

namespace rnoh {
namespace svg {

class SvgGroup : public SvgNode, public FontHolderBase {

public:
    SvgGroup() : SvgNode() { InitGroupFlag(); }
    ~SvgGroup() override = default;

private:
    // svg g, use
    void InitGroupFlag();

    void OnInitStyle() override;
};

} // namespace svg
} // namespace rnoh
