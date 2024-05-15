#pragma once

#include "SvgGroup.h"
#include "TextBase.h"

namespace rnoh {

class SvgText : public SvgGroup, public TextBase {
public:
    SvgText() = default;
    ~SvgText() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

private:
    void GlyphTraversal(OH_Drawing_Canvas *canvas);
};

} // namespace rnoh