#include "SvgSymbol.h"

namespace rnoh {
namespace svg {

void SvgSymbol::drawSymbol(OH_Drawing_Canvas *canvas, float width, float height) {
    LOG(INFO) << "[SvgSymbol::SvgSymbol] : ------drawSymbol mMinX :" << mMinX << " mMinY:" << mMinY
              << " mVbWidth : " << mVbWidth << " mVbHeight : " << mVbHeight << " mAlign : " << mAlign
              << " mMeetOrSlice : " << mMeetOrSlice;
    LOG(INFO) << "[SvgSymbol::SvgSymbol] : drawSymbol width :<< " << width << " height:" << height
              << " mAlign : " << mAlign;
    if (!mAlign.empty()) {
        Rect vbRect(vpToPx(mMinX), vpToPx(mMinY), vpToPx(mMinX + mVbWidth), vpToPx(mMinY + mVbHeight));
        Rect eRect(0,0, vpToPx(width), vpToPx(height));
        OH_Drawing_Matrix *viewBoxMatrix = ViewBox::getTransform(vbRect, eRect, mAlign, mMeetOrSlice);
        OH_Drawing_CanvasConcatMatrix(canvas, viewBoxMatrix);
        Draw(canvas);
    }
}

} // namespace svg
} // namespace rnoh