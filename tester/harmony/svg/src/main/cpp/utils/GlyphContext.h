
#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>
#include "properties/Dimension.h"
#include "utils/Utils.h"
#include "SvgNode.h"

namespace rnoh {

struct FontData {
    float random = 0.0f;
    // to be implemented
};

class GlyphContext {

private:
    std::vector<Dimension> mXs;
    std::vector<Dimension> mYs;
    std::vector<Dimension> mDXs;
    std::vector<Dimension> mDYs;
    std::vector<double> mRs;
    int mXsIndex = 0;
    int mYsIndex = 0;
    int mDXsIndex = 0;
    int mDYsIndex = 0;
    int mRsIndex = 0;
    int mXIndex = 0;
    int mYIndex = 0;
    int mDXIndex = 0;
    int mDYIndex = 0;
    int mRIndex = 0;
    int mTop = 0;
    float mScale = 0.0f;
    float mWidth = 0.0f;
    float mHeight = 0.0f;
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
    double mX = 0.0;
    double mY = 0.0;
    double mDX = 0.0;
    double mDY = 0.0;
    double mFontSize = 0.0;

    void pushIndices();

    void reset();

    FontData getFont() { return topFont; }

    FontData getTopOrParentFont(const std::shared_ptr<SvgNode> &child) {
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

    using ReadableMap = const std::unordered_map<std::string, std::string> &;
    void pushNodeAndFont(const std::shared_ptr<SvgNode> &node, ReadableMap font) {
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

    void pushContext(const std::shared_ptr<SvgNode>& node, ReadableMap font) {
        pushNodeAndFont(node, font);
        pushIndices();
    }

    using DimensionArray = const std::vector<Dimension> &;
    void pushContext(bool reset, const std::shared_ptr<SvgNode>& node, ReadableMap font, DimensionArray x, DimensionArray y, DimensionArray deltaX,
                     DimensionArray deltaY, DimensionArray rotate);

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