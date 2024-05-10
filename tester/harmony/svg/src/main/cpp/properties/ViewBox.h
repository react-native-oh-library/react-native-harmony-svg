//
// Created on 2024/5/9.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_VIEWBOX_H
#define HARMONY_VIEWBOX_H

#include "Rect.h"
#include <native_drawing/drawing_matrix.h>
#include <iostream>
#include <string>
#include <cmath>

namespace rhon{

class ViewBox {
private:
    static const int MOS_MEET = 0;
    static const int MOS_SLICE = 1;
    static const int MOS_NONE = 2;

public:
    static OH_Drawing_Matrix* getTransform(rnoh::Rect vbRect, rnoh::Rect eRect, std::string align, int meetOrSlice) {
        double vbX = vbRect.Left();
        double vbY = vbRect.Top();
        double vbWidth = vbRect.Width();
        double vbHeight = vbRect.Height();

        double eX = eRect.Left();
        double eY = eRect.Top();
        double eWidth = eRect.Width();
        double eHeight = eRect.Height();

        double scaleX = eWidth / vbWidth;
        double scaleY = eHeight / vbHeight;

        double translateX = eX - (vbX * scaleX);
        double translateY = eY - (vbY * scaleY);

        if (meetOrSlice == MOS_NONE) {
            double scale = std::min(scaleX, scaleY);

            if (scale > 1) {
                translateX -= (eWidth / scale - vbWidth) / 2;
                translateY -= (eHeight / scale - vbHeight) / 2;
            } else {
                translateX -= (eWidth - vbWidth * scale) / 2;
                translateY -= (eHeight - vbHeight * scale) / 2;
            }
        } else {
            if (!align.compare("none") && meetOrSlice == MOS_MEET) {
                scaleX = scaleY = std::min(scaleX, scaleY);
            } else if (!align.compare("none") && meetOrSlice == MOS_SLICE) {
                scaleX = scaleY = std::max(scaleX, scaleY);
            }

            if (align.find("xMid") != std::string::npos) {
                translateX += (eWidth - vbWidth * scaleX) / 2.0;
            }

            if (align.find("xMax") != std::string::npos) {
                translateX += (eWidth - vbWidth * scaleX);
            }

            if (align.find("YMid") != std::string::npos) {
                translateY += (eHeight - vbHeight * scaleY) / 2.0;
            }

            if (align.find("YMax") != std::string::npos) {
                translateY += (eHeight - vbHeight * scaleY);
            }
        }
        
        OH_Drawing_Matrix* transform = OH_Drawing_MatrixCreate();
        OH_Drawing_MatrixPostTranslate(transform, static_cast<float>(translateX), static_cast<float>(translateY));
        OH_Drawing_MatrixPreScale(transform, static_cast<float>(scaleX), static_cast<float>(scaleY), 0, 0);
        return transform;
    }
};

}
#endif //HARMONY_VIEWBOX_H
