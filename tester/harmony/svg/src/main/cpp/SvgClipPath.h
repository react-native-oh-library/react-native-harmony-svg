#pragma once

#include "SvgQuote.h"

namespace rnoh {
namespace svg {

    class SvgClipPath : public SvgQuote {

    public:
        SvgClipPath() = default;
        ~SvgClipPath() override = default;
    };
    
} // namespace svg
} // namespace rnoh