#include <string>
namespace rnoh {
namespace svg {

enum class AlignmentBaseline {
    baseline,
    textBottom,
    alphabetic,
    ideographic,
    middle,
    central,
    mathematical,
    textTop,
    bottom,
    center,
    top,
    /*
        SVG implementations may support the following aliases in order to support legacy content:

        text-before-edge = text-top
        text-after-edge = text-bottom
    */
    textBeforeEdge,
    textAfterEdge,
    // SVG 1.1
    beforeEdge,
    afterEdge,
    hanging,
};

enum class TextLengthAdjust { spacing, spacingAndGlyphs };

enum class TextPathMethod { align, stretch };
enum class TextPathMidLine { sharp, smooth };
enum class TextPathSide { left, right };
enum class TextPathSpacing { Auto, Exact };

AlignmentBaseline alignmentBaselineFromStr(const std::string &str);
TextLengthAdjust textLengthAdjustFromStr(const std::string &str);

TextPathMethod textPathMethodFromStr(const std::string &str);
TextPathSide textPathSideFromStr(const std::string &str);
TextPathMidLine textPathMidLineFromStr(const std::string &str);
TextPathSpacing textPathSpacingFromStr(const std::string &str);

} // namespace svg
} // namespace rnoh