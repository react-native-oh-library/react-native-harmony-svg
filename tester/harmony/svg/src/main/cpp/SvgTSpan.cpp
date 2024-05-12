#include <native_drawing/drawing_font_collection.h>
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_text_blob.h>
#include "SvgTSpan.h"
#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"
#include "properties/Offset.h"

namespace rnoh {
namespace {
const int MSCALE_X = 0; //!< use with getValues/setValues
const int MSKEW_X = 1;  //!< use with getValues/setValues
const int MTRANS_X = 2; //!< use with getValues/setValues
const int MSKEW_Y = 3;  //!< use with getValues/setValues
const int MSCALE_Y = 4; //!< use with getValues/setValues
const int MTRANS_Y = 5; //!< use with getValues/setValues
const int MPERSP_0 = 6; //!< use with getValues/setValues
const int MPERSP_1 = 7; //!< use with getValues/setValues
const int MPERSP_2 = 8; //!< use with getValues/setValues
}

void SvgTSpan::OnDraw(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        InitGlyph(canvas);
    }
    if (content.empty()) {
        for (const auto &child : children_) {
            if (auto tSpan = std::dynamic_pointer_cast<SvgTSpan>(child); tSpan) {
                tSpan->SetContext(glyphCtx_);
            }
        }
        return;
    }
    // if (inlineSize_) {
        DrawWrappedText(canvas);
    // } else {
        /* TODO: draw each character individually */
    // }
}

void SvgTSpan::DrawWrappedText(OH_Drawing_Canvas * canvas) {
    glyphCtx_->pushContext(false, shared_from_this(), x_, y_, dx_, dy_, rotate_);
    UpdateStrokeStyle();
    auto fillOpaque = UpdateFillStyle();
    if (!fillOpaque) {
        OH_Drawing_BrushSetColor(fillBrush_, Color::TRANSPARENT.GetValue());
    }
    drawing::TextStyle textStyle;
    textStyle.SetForegroundBrush(fillBrush_);
    textStyle.SetForegroundPen(strokePen_);
    textStyle.Update(font_);
    LOG(INFO) << "fontSize = " << font_->fontSize;
    drawing::TypographyStyle typographyStyle;
    typographyStyle.SetTextStyle(std::move(textStyle));
    typographyStyle.Update(font_);
    auto fontCollection = OH_Drawing_CreateFontCollection();
    auto typographyHandler = OH_Drawing_CreateTypographyHandler(typographyStyle.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, content.c_str());
    auto typography = OH_Drawing_CreateTypography(typographyHandler);
    double maxWidth = inlineSize_.value_or(Infinity<Dimension>()).ConvertToPx(OH_Drawing_CanvasGetWidth(canvas));
    LOG(INFO) << "TEXT GLYPH maxWidth = " << maxWidth;
    OH_Drawing_TypographyLayout(typography, maxWidth);
    double dx = glyphCtx_->nextX(0) + glyphCtx_->nextDeltaX();
    double dy = glyphCtx_->nextY() + glyphCtx_->nextDeltaY();
    LOG(INFO) << "TEXT GLYPH next X = " << dx << " next dy = " << dy;
    OH_Drawing_TypographyPaint(typography, canvas, dx, dy);

//     LOG(INFO) << "TEXT GLYPH current size = " << textSize.ToString();
    OH_Drawing_DestroyTypography(typography);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
    OH_Drawing_DestroyFontCollection(fontCollection);

    glyphCtx_->popContext();
}

double SvgTSpan::getTextAnchorOffset(TextAnchor textAnchor, const double &textMeasure) {
    switch (textAnchor) {
    default:
    case TextAnchor::start:
        return 0;

    case TextAnchor::middle:
        return -textMeasure / 2;

    case TextAnchor::end:
        return -textMeasure;
    }
}

void SvgTSpan::getLinePath(std::string line, OH_Drawing_Canvas *canvas) {
    int length = line.size();
    if (length == 0) {
        return;
    }
    
    double pathLength = 0;
    bool isClosed = false;
    bool hasTextPath = textPath_ != nullptr;
    if (hasTextPath) {
        pathLength = OH_Drawing_PathGetLength(textPath_->getTextPath(), false);
        isClosed = OH_Drawing_PathIsClosed(textPath_->getTextPath(), false);
        if (pathLength == 0) {
            return;
        }
    }

    drawing::TextStyle textStyle;
    textStyle.SetForegroundBrush(fillBrush_);
    textStyle.SetForegroundPen(strokePen_);
    textStyle.Update(font_);
    drawing::TypographyStyle typographyStyle;
    typographyStyle.SetTextStyle(std::move(textStyle));
    auto fontCollection = OH_Drawing_CreateFontCollection();
    auto typographyHandler = OH_Drawing_CreateTypographyHandler(typographyStyle.typographyStyle_.get(), fontCollection);

    OH_Drawing_TypographyHandlerAddText(typographyHandler, line.c_str());
    auto typography = OH_Drawing_CreateTypography(typographyHandler);
    OH_Drawing_TypographyLayout(typography, 1e9);
    
    //TODO ligature
    const char* chars = line.c_str();
    
    //TODO paint.getTextWidths(line, advances) no corresponding API
    
    //TODO TextAnchor
    TextAnchor textAnchor = font_->textAnchor;
//     double textMeasure = anchorRoot.getSubtreeTextChunksTotalAdvance(paint);
    double textMeasure = 0;
    double offset = getTextAnchorOffset(textAnchor, textMeasure);

    int side = 1;
    double startOfRendering = 0;
    double endOfRendering = pathLength;
    double fontSize = font_->fontSize;
    bool sharpMidLine = false;
    if(hasTextPath) {
        sharpMidLine = textPath_->getMidLine() == TextPathMidLine::sharp;
        side = textPath_->getSide() == TextPathSide::right ? -1 : 1;
//         double absoluteStartOffset = getAbsoluteStartOffset(textPath.getStartOffset(), pathLength, fontSize);
        double absoluteStartOffset = textPath_->getStartOffset();
        offset += absoluteStartOffset;
        if(isClosed) {
            double halfPathDistance = pathLength / 2;
            startOfRendering = absoluteStartOffset + (textAnchor == TextAnchor::middle ? -halfPathDistance : 0);
            endOfRendering = startOfRendering + pathLength;
        }
    }

    double scaleSpacingAndGlyphs = 1.0;
    double scaledDirection = scaleSpacingAndGlyphs * side;
    
    //TODO textLength and lengthAdjust
    OH_Drawing_Font_Metrics* fm;
    OH_Drawing_TextStyleGetFontMetrics(typography, textStyle.textStyle_.get(), fm);
    
    double descendarDepth = fm->descent;
    double bottom = descendarDepth + fm->leading;
    double ascenderHeight = -fm->ascent + fm->leading;
    double top = -fm->top;
    //TODO destroy FontMetrics?
    double totalHeight = top + bottom;
    double baselineShift = 0;
    //TODO getBaselineShift()
    //TODO getAlignmentBaseline()

    OH_Drawing_Matrix* start;
    OH_Drawing_Matrix *mid;
    OH_Drawing_Matrix *end;
    std::vector<double> startPointMatrixData(9);
    std::vector<double> endPointMatrixData(9);
    
    for (int index = 0; index < length; index++) {
        auto currentChar = chars[index];
        std::string current = std::string(1, currentChar);
        
        /*
          Determine the glyph's charwidth (i.e., the amount which the current text position
          advances horizontally when the glyph is drawn using horizontal text layout).
      */
        bool alreadyRenderedGraphemeCluster = false;
        bool hasLigature = false;
        OH_Drawing_Font* textFont;
        auto textBlob =
            OH_Drawing_TextBlobCreateFromString(&currentChar, textFont, TEXT_ENCODING_UTF8);

        OH_Drawing_Rect* textBounds;
        OH_Drawing_TextBlobGetBounds(textBlob, textBounds);
        double charWidth = OH_Drawing_RectGetWidth(textBounds);
        OH_Drawing_TextBlobDestroy(textBlob);
        OH_Drawing_RectDestroy(textBounds);
        //TODO double charWidth = paint.measureText(current) * scaleSpacingAndGlyphs;

        bool isWordSeparator = currentChar == ' ';
        double wordSpace = isWordSeparator ? font_->wordSpacing : 0;
        double spacing = wordSpace + font_->letterSpacing;
        double advance = charWidth + spacing;
        
        double x = glyphCtx_->nextX(alreadyRenderedGraphemeCluster ? 0 : advance);
        double y = glyphCtx_->nextY();
        double dx = glyphCtx_->nextDeltaX();
        double dy = glyphCtx_->nextDeltaY();
        double r = glyphCtx_->nextRotation();
        
        advance *= side;
        charWidth *= side;
        double cursor = offset + (x + dx) * side;
        double startPoint = cursor - advance;
        
        if (hasTextPath) {
            double endPoint = startPoint + charWidth;
            double halfWay = charWidth / 2;
            double midPoint = startPoint + halfWay;
            
            if (midPoint > endOfRendering) {
                continue;
            } else if (midPoint < startOfRendering) {
                continue;
            }
            if (sharpMidLine) {
                OH_Drawing_PathGetMatrix(textPath_->getTextPath(), false, midPoint, mid, GET_POSITION_MATRIX);
            } else {
                if (startPoint < 0) {
                    OH_Drawing_PathGetMatrix(textPath_->getTextPath(), false, startPoint, start, GET_POSITION_MATRIX);
                    OH_Drawing_MatrixTranslate(start, startPoint, 0);
                } else {
                    OH_Drawing_PathGetMatrix(textPath_->getTextPath(), false, startPoint, start, GET_POSITION_MATRIX);
                }
                OH_Drawing_PathGetMatrix(textPath_->getTextPath(), false, midPoint, mid, GET_POSITION_MATRIX);
                
                if(endPoint > pathLength) {
                    OH_Drawing_PathGetMatrix(textPath_->getTextPath(), false, pathLength, end, GET_POSITION_MATRIX);
                    OH_Drawing_MatrixPreTranslate(end, (endPoint - pathLength), 0);
                } else {
                    OH_Drawing_PathGetMatrix(textPath_->getTextPath(), false, endPoint, end, GET_POSITION_MATRIX);
                }
                for (int i = 0; i < 9; i++) {
                    startPointMatrixData[i] = OH_Drawing_MatrixGetValue(start, i);
                    endPointMatrixData[i] = OH_Drawing_MatrixGetValue(end, i);
                }
                
                double startX = startPointMatrixData[MTRANS_X];
                double startY = startPointMatrixData[MTRANS_Y];
                double endX = endPointMatrixData[MTRANS_X];
                double endY = endPointMatrixData[MTRANS_Y];

                // line through the startpoint-on-the-path and the endpoint-on-the-path
                double lineX = endX - startX;
                double lineY = endY - startY;

                double glyphMidlineAngle = std::atan2(lineY, lineX);
                OH_Drawing_MatrixPreRotate(mid, (glyphMidlineAngle * radToDeg * side), 0, 0);
            }
            /*
            Align the glyph vertically relative to the midpoint-on-the-path based on property
            alignment-baseline and any specified values for attribute ‘dy’ on a ‘tspan’ element.
        */
            OH_Drawing_MatrixPreTranslate(mid, -halfWay, (dy + baselineShift));
            OH_Drawing_MatrixPreScale(mid, scaledDirection, side, 0, 0);
            OH_Drawing_MatrixPostTranslate(mid, 0, y);
        } else {
            OH_Drawing_MatrixTranslate(mid, startPoint, (y + dy + baselineShift));
        }
        OH_Drawing_MatrixPreRotate(mid, r, 0, 0);
        OH_Drawing_Path* glyph;
        if(hasLigature) {
            // TODO hasLigature
        } else {
            
        }
        OH_Drawing_Rect* bounds; 
        OH_Drawing_PathGetBounds(glyph, bounds);
        float width = OH_Drawing_RectGetWidth(bounds);
        if (width == 0) {
            //TODO Render unicode emoji
        } else {
            //TODO Transform Canvas and Draw
        }
        
        OH_Drawing_RectDestroy(bounds);
    }
    OH_Drawing_DestroyTypography(typography);
    OH_Drawing_DestroyTypographyHandler(typographyHandler);
    OH_Drawing_DestroyFontCollection(fontCollection);
    OH_Drawing_MatrixDestroy(start);
    OH_Drawing_MatrixDestroy(mid);
    OH_Drawing_MatrixDestroy(end);
}

} // namespace rnoh