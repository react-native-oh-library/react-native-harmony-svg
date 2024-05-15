#pragma once
#include <cmath>
#include "SvgGraphic.h"
#include "SvgText.h"
#include <native_drawing/drawing_text_typography.h>
#include "SvgTextPath.h"
#include "utils/GlyphContext.h"
#include "drawing/TypographyStyle.h"
#include "TextBase.h"
#include "FontHolderBase.h"

namespace rnoh {
class SvgTSpan : public SvgGraphic, public TextBase, public FontHolderBase {
public:
    SvgTSpan() {
        hrefFill_ = true;
        hrefRender_ = true;
        passStyle_ = true;
        inheritStyle_ = true;
        drawTraversed_ = true;
    }
    ~SvgTSpan() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    void SetTextPathRef(std::shared_ptr<SvgTextPath> textPath) { textPath_ = textPath; }
    
    double getTextAnchorOffset(TextAnchor textAnchor, const double &textMeasure);
    
    std::string content_;

private:
    void DrawTextPath(OH_Drawing_Canvas* canvas);
    void DrawText(OH_Drawing_Canvas* canvas);

    drawing::TypographyStyle PrepareTypoStyle();

    /**
     * @return true if spacing needs to be adjusted.
     */
    bool AdjustSpacing(OH_Drawing_Canvas *canvas, double textMeasure, double& scaleSpacingAndGlyphs);

    double CalcBaselineShift(OH_Drawing_TypographyCreate* handler, OH_Drawing_TextStyle* style, const OH_Drawing_Font_Metrics& fm);

    std::shared_ptr<SvgTextPath> textPath_;
};

} // namespace rnoh