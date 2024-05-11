
#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>
#include "properties/Dimension.h"
#include "utils/Utils.h"
#include "SvgText.h"

namespace rnoh {

struct FontData {
    // implementation details
};

class GlyphContext {
    using ReadableMap = const std::unordered_map<std::string, std::string> &;

private:
    std::vector<Dimension> mXs;
    std::vector<Dimension> mYs;
    std::vector<Dimension> mDXs;
    std::vector<Dimension> mDYs;
    std::vector<double> mRs;
    int mXsIndex;
    int mYsIndex;
    int mDXsIndex;
    int mDYsIndex;
    int mRsIndex;
    int mXIndex;
    int mYIndex;
    int mDXIndex;
    int mDYIndex;
    int mRIndex;
    int mTop;
    float mScale;
    float mWidth;
    float mHeight;
    std::vector<int> mXsIndices;
    std::vector<int> mYsIndices;
    std::vector<int> mDXsIndices;
    std::vector<int> mDYsIndices;
    std::vector<int> mRsIndices;
    std::vector<std::vector<Dimension>> mXsContext;
    std::vector<std::vector<Dimension>> mYsContext;
    std::vector<std::vector<Dimension>> mDXsContext;
    std::vector<std::vector<Dimension>> mDYsContext;
    std::vector<std::vector<double>> mRsContext;
    std::vector<int> mXIndices;
    std::vector<int> mYIndices;
    std::vector<int> mDXIndices;
    std::vector<int> mDYIndices;
    std::vector<int> mRIndices;
    std::vector<FontData> mFontContext;
    FontData topFont;
    double mX;
    double mY;
    double mDX;
    double mDY;
    double mFontSize;

    void pushIndices();

    void reset();

    FontData getFont() { return topFont; }

    FontData getTopOrParentFont(std::shared_ptr<SvgGraphic> child) {
        // if (mTop > 0) {
        //     return topFont;
        // } else {
        //     std::shared_ptr<SvgGraphic> parentRoot = child->getParentTextRoot();

        //     while (parentRoot != nullptr) {
        //         FontData map = parentRoot->getGlyphContext().getFont();
        //         if (map != FontData.Defaults) {
        //             return map;
        //         }
        //         parentRoot = parentRoot->getParentTextRoot();
        //     }

        //     return FontData.Defaults;
        // }
        return {};
    }

    void pushNodeAndFont(std::shared_ptr<SvgGraphic> node, ReadableMap font) {
        FontData parent = getTopOrParentFont(node);
        mTop++;

        // if (!font.has_value()) {
        //     mFontContext.push_back(parent);
        //     return;
        // }

        // FontData data = FontData(font.value(), parent, mScale);
        // mFontSize = data.fontSize;
        // mFontContext.push_back(data);
        // topFont = data;
    }

public:
    GlyphContext(float scale, float width, float height);

    void pushContext(std::shared_ptr<SvgGraphic> node, ReadableMap font) {
        pushNodeAndFont(node, font);
        pushIndices();
    }

    void pushContext(bool reset, std::shared_ptr<SvgText> node, ReadableMap font, std::vector<Dimension> x,
                     std::vector<Dimension> y, std::vector<Dimension> deltaX, std::vector<Dimension> deltaY,
                     std::vector<Dimension> rotate);

    void popContext();

    static void incrementIndices(std::vector<int> &indices, int topIndex);

    double getFontSize() { return mFontSize; }

    double nextX(double advance);

    double nextY();

    double nextDeltaX();

    double nextDeltaY();

    double nextRotation();

    float getWidth() { return mWidth; }

    float getHeight() { return mHeight; }
};
} // namespace rnoh