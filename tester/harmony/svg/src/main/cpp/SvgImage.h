//
// Created on 2024/5/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

// #ifndef HARMONY_SVGIMAGE_H
// #define HARMONY_SVGIMAGE_H
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_IMAGE_H

#include <string>
#include "SvgGraphic.h"
// #include <rawfile/raw_file.h>
// #include <rawfile/raw_file_manager.h>
// #include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_image.h>
#include <native_drawing/drawing_rect.h>
#include <native_drawing/drawing_pixel_map.h>
#include <native_drawing/drawing_sampling_options.h>
#include "utils/Utils.h"
#include <multimedia/image_framework/image_mdk_common.h>
#include <multimedia/image_framework/image/image_source_native.h>
#include <multimedia/image_framework/image_pixel_map_mdk.h>

namespace rnoh {

class SvgImage : public svg::SvgGraphic {
public:
    SvgImage() = default;
    ~SvgImage() override = default;
    // onProps changed 进行修改
    float x;
    float y;
    float width;
    float height;
    float opacity;
    std::string align;
    int meetOrSlice;
    facebook::react::ImageSource src;
    void OnDraw(OH_Drawing_Canvas *canvas) override;
//     OH_Drawing_Path *AsPath() override;

};

} // namespace rnoh

#endif //HARMONY_SVGIMAGE_H
