#pragma once
#include "SvgGraphic.h"

namespace rnoh {
namespace svg {
class SvgPath : public SvgGraphic {
    private:
        std::string d;

    public:
        SvgPath() = default;
        ~SvgPath() override = default;

        void setD(std::string d);

        OH_Drawing_Path *AsPath() override;
};

} // namespace svg
} // namespace rnoh