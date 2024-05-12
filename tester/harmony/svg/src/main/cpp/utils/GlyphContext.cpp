#include "GlyphContext.h"
namespace rnoh {

void GlyphContext::pushContext(bool reset, const std::shared_ptr<SvgNode>& node, ReadableMap font, DimensionArray x, DimensionArray y,
                               DimensionArray deltaX, DimensionArray deltaY, DimensionArray rotate) {
    if (reset) {
        this->reset();
    }

    LOG(INFO) << "GLYPH PUSHING" << " mTop = " << mTop << " node = " << node;
    pushNodeAndFont(node, font);

    if (!x.empty()) {
        mXsIndex++;
        mXIndex = -1;
        mXIndices.push_back(mXIndex);
        mXs = x;
        mXsContext.push_back(mXs);
    }

    if (!y.empty()) {
        mYsIndex++;
        mYIndex = -1;
        mYIndices.push_back(mYIndex);
        mYs = y;
        mYsContext.push_back(mYs);
    }

    if (!deltaX.empty()) {
        mDXsIndex++;
        mDXIndex = -1;
        mDXIndices.push_back(mDXIndex);
        mDXs = deltaX;
        mDXsContext.push_back(mDXs);
    }

    if (!deltaY.empty()) {
        mDYsIndex++;
        mDYIndex = -1;
        mDYIndices.push_back(mDYIndex);
        mDYs = deltaY;
        mDYsContext.push_back(mDYs);
    }

    if (!rotate.empty()) {
        mRsIndex++;
        mRIndex = -1;
        mRIndices.push_back(mRIndex);
        // convert Dimension vector to double
        mRs.clear();
        for (const auto &ro : rotate) {
            mRs.emplace_back(ro.Value());
        }
        mRsContext.push_back(mRs);
    }

    pushIndices();
}
void GlyphContext::popContext() {
    mFontContext.pop_back();
    mXsIndices.pop_back();
    mYsIndices.pop_back();
    mDXsIndices.pop_back();
    mDYsIndices.pop_back();
    mRsIndices.pop_back();

    mTop--;

    int x = mXsIndex;
    int y = mYsIndex;
    int dx = mDXsIndex;
    int dy = mDYsIndex;
    int r = mRsIndex;

    LOG(INFO) << "GLYPH mTop = " << mTop << " mXsIndices size = " << mXsIndices.size();
    topFont = mFontContext[mTop];
    mXsIndex = mXsIndices[mTop];
    mYsIndex = mYsIndices[mTop];
    mDXsIndex = mDXsIndices[mTop];
    mDYsIndex = mDYsIndices[mTop];
    mRsIndex = mRsIndices[mTop];

    if (x != mXsIndex) {
        mXsContext.erase(mXsContext.begin() + x);
        mXs = mXsContext[mXsIndex];
        mXIndex = mXIndices[mXsIndex];
    }
    if (y != mYsIndex) {
        mYsContext.erase(mYsContext.begin() + y);
        mYs = mYsContext[mYsIndex];
        mYIndex = mYIndices[mYsIndex];
    }
    if (dx != mDXsIndex) {
        mDXsContext.erase(mDXsContext.begin() + dx);
        mDXs = mDXsContext[mDXsIndex];
        mDXIndex = mDXIndices[mDXsIndex];
    }
    if (dy != mDYsIndex) {
        mDYsContext.erase(mDYsContext.begin() + dy);
        mDYs = mDYsContext[mDYsIndex];
        mDYIndex = mDYIndices[mDYsIndex];
    }
    if (r != mRsIndex) {
        mRsContext.erase(mRsContext.begin() + r);
        mRs = mRsContext[mRsIndex];
        mRIndex = mRIndices[mRsIndex];
    }
}
double GlyphContext::nextX(double advance) {
    incrementIndices(mXIndices, mXsIndex);

    int nextIndex = mXIndex + 1;
    if (nextIndex < mXs.size()) {
        mDX = 0;
        mXIndex = nextIndex;
        Dimension string = mXs[nextIndex];
        mX = string.ConvertToPx(mWidth);
    }

    mX += advance;

    return mX;
}
double GlyphContext::nextDeltaX() {
    incrementIndices(mDXIndices, mDXsIndex);

    int nextIndex = mDXIndex + 1;
    if (nextIndex < mDXs.size()) {
        mDXIndex = nextIndex;
        Dimension string = mDXs[nextIndex];
        double val = string.ConvertToPx(mWidth);
        mDX += val;
    }

    return mDX;
}
double GlyphContext::nextDeltaY() {
    incrementIndices(mDYIndices, mDYsIndex);

    int nextIndex = mDYIndex + 1;
    if (nextIndex < mDYs.size()) {
        mDYIndex = nextIndex;
        Dimension string = mDYs[nextIndex];
        double val = string.ConvertToPx(mHeight);
        mDY += val;
    }

    return mDY;
}
double GlyphContext::nextRotation() {
    incrementIndices(mRIndices, mRsIndex);

    mRIndex = std::min(mRIndex + 1, static_cast<int>(mRs.size()) - 1);

    return mRs[mRIndex];
}
double GlyphContext::nextY() {
    incrementIndices(mYIndices, mYsIndex);

    int nextIndex = mYIndex + 1;
    if (nextIndex < mYs.size()) {
        mDY = 0;
        mYIndex = nextIndex;
        Dimension string = mYs[nextIndex];
        mY = string.ConvertToPx(mHeight);
    }

    return mY;
}
void GlyphContext::incrementIndices(std::vector<int> &indices, int topIndex) {
    for (int index = topIndex; index >= 0; index--) {
        int xIndex = indices[index];
        indices[index] = xIndex + 1;
    }
}
GlyphContext::GlyphContext(float scale, float width, float height) : mScale(scale), mWidth(width), mHeight(height) {
    mXsContext.push_back(mXs);
    mYsContext.push_back(mYs);
    mDXsContext.push_back(mDXs);
    mDYsContext.push_back(mDYs);
    mRsContext.push_back(mRs);

    mXIndices.push_back(mXIndex);
    mYIndices.push_back(mYIndex);
    mDXIndices.push_back(mDXIndex);
    mDYIndices.push_back(mDYIndex);
    mRIndices.push_back(mRIndex);

    mFontContext.push_back(topFont);

    pushIndices();
}
void GlyphContext::pushIndices() {
    mXsIndices.push_back(mXsIndex);
    mYsIndices.push_back(mYsIndex);
    mDXsIndices.push_back(mDXsIndex);
    mDYsIndices.push_back(mDYsIndex);
    mRsIndices.push_back(mRsIndex);
}
void GlyphContext::reset() {
    mXsIndex = mYsIndex = mDXsIndex = mDYsIndex = mRsIndex = 0;
    mXIndex = mYIndex = mDXIndex = mDYIndex = mRIndex = -1;
    mX = mY = mDX = mDY = 0;
}
} // namespace rnoh