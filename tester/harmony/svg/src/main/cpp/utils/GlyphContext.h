#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>
#include "properties/Dimension.h"
#include "utils/Utils.h"
#include "SvgNode.h"

namespace rnoh {
namespace svg {

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
    double mX = 0.0;
    double mY = 0.0;
    double mDX = 0.0;
    double mDY = 0.0;

    void pushIndices();

    void reset();

    void pushNode(const std::shared_ptr<SvgNode> &node) {
        mTop++;
    }

public:
    GlyphContext(float scale, float width, float height);

    void pushContext(const std::shared_ptr<SvgNode>& node) {
        pushNode(node);
        pushIndices();
    }

    using DimensionArray = const std::vector<Dimension> &;
    void pushContext(bool reset, const std::shared_ptr<SvgNode>& node, DimensionArray x, DimensionArray y, DimensionArray deltaX,
                     DimensionArray deltaY, DimensionArray rotate);

    void popContext();

    static void incrementIndices(std::vector<int> &indices, int topIndex);

    /**
     * @param advance in x position by the next span.
     * @return x position for this next span.
     */
    double nextX(double advance);

    double nextY();

    double nextDeltaX();

    double nextDeltaY();

    double nextRotation();

    float getWidth() { return mWidth; }
    

    float getHeight() { return mHeight; }
};

} // namespace svg
} // namespace rnoh