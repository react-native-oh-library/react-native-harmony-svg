//
// Created on 2024/5/9.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_VIEWBOX_H
#define HARMONY_VIEWBOX_H

#include "Rect.h"
#include "drawing/Matrix.h"
#include <string>
#include <glog/logging.h>

namespace rnoh {
namespace svg {

class ViewBox {
private:
    static const int MOS_MEET = 0;
    static const int MOS_SLICE = 1;
    static const int MOS_NONE = 2;

public:
    static drawing::Matrix getTransform(const Rect &vbRect, const Rect &eRect, const std::string &align, const int &meetOrSlice) {
        // based on https://svgwg.org/svg2-draft/coords.html#ComputingAViewportsTransform

        // Let vb-x, vb-y, vb-width, vb-height be the min-x, min-y, width and height values of the
        // viewBox attribute respectively.
        double vbX = vbRect.Left();
        double vbY = vbRect.Top();
        double vbWidth = vbRect.Width();
        double vbHeight = vbRect.Height();

        // Let e-x, e-y, e-width, e-height be the position and size of the element respectively.
        double eX = eRect.Left();
        double eY = eRect.Top();
        double eWidth = eRect.Width();
        double eHeight = eRect.Height();

        // Initialize scale-x to e-width/vb-width.
        double scaleX = eWidth / vbWidth;

        // Initialize scale-y to e-height/vb-height.
        double scaleY = eHeight / vbHeight;

        // Initialize translate-x to e-x - (vb-x * scale-x).
        // Initialize translate-y to e-y - (vb-y * scale-y).
        double translateX = eX - (vbX * scaleX);
        double translateY = eY - (vbY * scaleY);

        // If meetOrSlice is 'none'
        if (meetOrSlice == MOS_NONE) {
            // Let scale be set the smaller value of scale-x and scale-y.
            // Assign scale-x and scale-y to scale.
            double scale = scaleX = scaleY =  std::min(scaleX, scaleY);

            // If scale is greater than 1
            if (scale > 1) {
                // Minus translateX by (eWidth / scale - vbWidth) / 2
                // Minus translateY by (eHeight / scale - vbHeight) / 2
                translateX -= (eWidth / scale - vbWidth) / 2;
                translateY -= (eHeight / scale - vbHeight) / 2;
            } else {
                translateX -= (eWidth - vbWidth * scale) / 2;
                translateY -= (eHeight - vbHeight * scale) / 2;
            }
        } else {
            // If align is not 'none' and meetOrSlice is 'meet', set the larger of scale-x and scale-y to
            // the smaller.
            // Otherwise, if align is not 'none' and meetOrSlice is 'slice', set the smaller of scale-x
            // and scale-y to the larger.
            if (align != "none" && meetOrSlice == MOS_MEET) {
                scaleX = scaleY = std::min(scaleX, scaleY);
            } else if (align != "none" && meetOrSlice == MOS_SLICE) {
                scaleX = scaleY = std::max(scaleX, scaleY);
            }

            // If align contains 'xMid', add (e-width - vb-width * scale-x) / 2 to translate-x.
            if (align.find("xMid") != std::string::npos) {
                translateX += (eWidth - vbWidth * scaleX) / 2.0;
            }

            // If align contains 'xMax', add (e-width - vb-width * scale-x) to translate-x.
            if (align.find("xMax") != std::string::npos) {
                translateX += (eWidth - vbWidth * scaleX);
            }

            // If align contains 'yMid', add (e-height - vb-height * scale-y) / 2 to translate-y.
            if (align.find("YMid") != std::string::npos) {
                translateY += (eHeight - vbHeight * scaleY) / 2.0;
            }

            // If align contains 'yMax', add (e-height - vb-height * scale-y) to translate-y.
            if (align.find("YMax") != std::string::npos) {
                translateY += (eHeight - vbHeight * scaleY);
            }
        }

        // The transform applied to content contained by the element is given by
        // translate(translate-x, translate-y) scale(scale-x, scale-y).
        drawing::Matrix transform;
        transform.PostTranslate(static_cast<float>(translateX), static_cast<float>(translateY));
        transform.PreScale(static_cast<float>(scaleX), static_cast<float>(scaleY), 0, 0);
        return transform;
    }
};

} // namespace svg
} // namespace rnoh
#endif // HARMONY_VIEWBOX_H
