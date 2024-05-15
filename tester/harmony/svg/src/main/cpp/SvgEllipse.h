#pragma once
//
// Created on 2024/5/4.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "SvgGraphic.h"

namespace rnoh {
namespace svg {

class SvgEllipse : public SvgGraphic {
public:
    using Float = facebook::react::Float;
    SvgEllipse() = default;
    ~SvgEllipse() override = default;
    Float cx;
    Float cy;
    Float rx;
    Float ry;
    uint32_t colorFill;
    uint32_t strokeColor;
    uint32_t strokeWith;
    OH_Drawing_Path *AsPath() override;
};

} // namespace svg
} // namespace rnoh


