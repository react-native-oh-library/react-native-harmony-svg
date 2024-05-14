#include "TextProperties.h"
namespace rnoh {
TextPathMethod textPathMethodFromStr(const std::string &str) {
    if (str == "stretch") {
        return TextPathMethod::stretch;
    } else {
        return TextPathMethod::align;
    }
}

TextPathSide textPathSideFromStr(const std::string &str) {
    if (str == "right") {
        return TextPathSide::right;
    } else {
        return TextPathSide::left;
    }
}

TextPathMidLine textPathMidLineFromStr(const std::string &str) {
    if (str == "sharp") {
        return TextPathMidLine::sharp;
    } else {
        return TextPathMidLine::smooth;
    }
}

TextPathSpacing textPathSpacingFromStr(const std::string &str) {
    if (str == "auto") {
        return TextPathSpacing::Auto;
    } else {
        return TextPathSpacing::Exact;
    }
}

TextLengthAdjust textLengthAdjustFromStr(const std::string &str) {
    if (str == "spacing") {
        return TextLengthAdjust::spacing;
    } else {
        return TextLengthAdjust::spacingAndGlyphs;
    }

}

AlignmentBaseline alignmentBaselineFromStr(const std::string &str) {
    if (str == "baseline") {
        return AlignmentBaseline::baseline;
    } else if (str == "text-bottom") {
        return AlignmentBaseline::textBottom;
    } else if (str == "alphabetic") {
        return AlignmentBaseline::alphabetic;
    } else if (str == "ideographic") {
        return AlignmentBaseline::ideographic;
    } else if (str == "middle") {
        return AlignmentBaseline::middle;
    } else if (str == "central") {
        return AlignmentBaseline::central;
    } else if (str == "mathematical") {
        return AlignmentBaseline::mathematical;
    } else if (str == "text-top") {
        return AlignmentBaseline::textTop;
    } else if (str == "bottom") {
        return AlignmentBaseline::bottom;
    } else if (str == "center") {
        return AlignmentBaseline::center;
    } else if (str == "top") {
        return AlignmentBaseline::top;
    } else if (str == "text-before-edge") {
        return AlignmentBaseline::textBeforeEdge;
    } else if (str == "text-after-edge") {
        return AlignmentBaseline::textAfterEdge;
    } else if (str == "before-edge") {
        return AlignmentBaseline::beforeEdge;
    } else if (str == "after-edge") {
        return AlignmentBaseline::afterEdge;
    } else if (str == "hanging") {
        return AlignmentBaseline::hanging;
    } else {
        return AlignmentBaseline::baseline;
    }
}
}