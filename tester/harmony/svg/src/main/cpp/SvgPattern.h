#pragma once

#include <string>
#include "SvgQuote.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {

class SvgPattern : public SvgQuote {

public:
    using Float = facebook::react::Float;
    SvgPattern();
    ~SvgPattern() = default;
    
    virtual void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) override;
    virtual void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) override;
    void SaveDefinition(OH_Drawing_Canvas *canvas);
    void ConcatMatrix(OH_Drawing_Canvas *canvas);
    const Pattern &GetPatternAttr() const;

    void setPatternX(Dimension x);

    void setPatternY(Dimension y);

    void setHeight(Dimension height);

    void setWidth(Dimension width);

    void setPatternUnits(int patternUnits);

    void setPatternContentUnits(int patternContentUnits);

    void setViewBox(Rect viewBox);

    void setImage(OH_Drawing_Image *image);

    void setmMinX(float mMinX);

    void setmMinY(float mMinUY);

    void setmVbWidth(float mVbWidth);

    void setmVbHeight(float mVbHeight);

    void setmAlign(std::string mAlign);

    void setmMeetOrSlice(int mMeetOrSlice);

    void setPatternTransforms(std::vector<Float> gradientTransforms);
private:
    Pattern pattern;
    double scale_ = 3.25010318;
  };
}