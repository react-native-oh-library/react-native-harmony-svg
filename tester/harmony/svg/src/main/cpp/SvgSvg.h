#pragma once

#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_path.h>
#include "SvgGroup.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {
class SvgSvg : public SvgGroup {
public:
    SvgSvg();
    ~SvgSvg() override = default;

    OH_Drawing_Path *AsPath() const override;

    Size GetSize() const;

    Rect GetViewBox() const;
    
    void Draw(OH_Drawing_Canvas *canvas) override;

    SvgAttributes attr_;

private:
    void FitCanvas(OH_Drawing_Canvas *canvas);
};

} // namespace rnoh
