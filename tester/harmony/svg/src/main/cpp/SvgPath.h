#pragma once
#include "SvgGraphic.h"

namespace rnoh {
namespace svg {
class SvgPath : public SvgGraphic {
public:
    SvgPath() = default;
    ~SvgPath() override = default;
    
    std::string d;

    void setD(std::string d);

    OH_Drawing_Path *AsPath() override;
};

} // namespace svg
} // namespace rnoh