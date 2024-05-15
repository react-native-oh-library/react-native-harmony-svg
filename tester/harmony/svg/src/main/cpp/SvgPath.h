#pragma once
#include "SvgGraphic.h"

namespace rnoh {
namespace svg {
class SvgPath : public SvgGraphic {
public:
    SvgPath() = default;
    ~SvgPath() override = default;
    
    std::string d;
    
    drawing::Path AsPath() override;
};

} // namespace svg
} // namespace rnoh