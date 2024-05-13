#include "SvgSymbol.h"

namespace rnoh {

void SvgSymbol::drawSymbol(OH_Drawing_Canvas *canvas, float width, float height) {
    LOG(INFO) << "[SvgSymbol::SvgSymbol] : ------drawSymbol mMinX :" << mMinX << " mMinY:" << mMinY
              << " mVbWidth : " << mVbWidth << " mVbHeight : " << mVbHeight << " mAlign : " << mAlign
              << " mMeetOrSlice : " << mMeetOrSlice;
    LOG(INFO) << "[SvgSymbol::SvgSymbol] : drawSymbol width :<< " << width << " height:" << height
              << " mAlign : " << mAlign;
    if (!mAlign.empty()) {
        LOG(INFO) << "[SvgSymbol::SvgSymbol] : drawSymbol start";
        Rect vbRect(mMinX * scale_, mMinY * scale_, (mMinX + mVbWidth) * scale_, (mMinY + mVbHeight) * scale_);
        Rect eRect(0, 0, width / scale_, height / scale_);
        OH_Drawing_Matrix *viewBoxMatrix = rnoh::ViewBox::getTransform(vbRect, eRect, mAlign, mMeetOrSlice);
        OH_Drawing_CanvasConcatMatrix(canvas, viewBoxMatrix);
        Draw(canvas);
    }
}
} // namespace rnoh