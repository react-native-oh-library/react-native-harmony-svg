//
// Created on 2025/10/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SVGFOREIGNOBJECTNODEDELEGATE_H
#define HARMONY_SVGFOREIGNOBJECTNODEDELEGATE_H
#include "SvgForeignProps.h"
class SvgForeignObjectNodeDelegate {
public:
    virtual ~SvgForeignObjectNodeDelegate() = default;
    virtual void onDrawForeignImage(ForeignProps props){};
};
#endif //HARMONY_SVGFOREIGNOBJECTNODEDELEGATE_H
