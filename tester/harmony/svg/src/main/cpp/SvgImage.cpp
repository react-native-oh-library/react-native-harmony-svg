/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SvgImage.h"
#include "utils/StringUtils.h"

namespace rnoh {
namespace svg {

void SvgImage::OnDraw(OH_Drawing_Canvas *canvas) {
    x = svg::vpToPx(x), y = svg::vpToPx(y), width = svg::vpToPx(width), height = svg::vpToPx(height);
    if (src.uri.size() != 0) {
        OH_ImageSourceNative *res;
        OH_PixelmapNative *pixelmap;
        OH_DecodingOptions *options;

        int len = src.uri.size();
        char *srcUri = const_cast<char *>(src.uri.c_str());

        OH_DecodingOptions_Create(&options);
        OH_ImageSourceNative_CreateFromUri(srcUri, len, &res);
        auto code = OH_ImageSourceNative_CreatePixelmap(res, options, &pixelmap);
        LOG(INFO) << "[SvgImage] code: " << code;

        if (code == 0) {
            OH_PixelmapNative_Opacity(pixelmap, opacity);

            // get the real width and height from pixelmap(OH_PixelmapNative *).
            OH_Pixelmap_ImageInfo *info;
            OH_PixelmapImageInfo_Create(&info);
            OH_PixelmapNative_GetImageInfo(pixelmap, info);

            // get the resource properties: width and height
            uint32_t *imageWidth = new uint32_t;
            uint32_t *imageHeight = new uint32_t;
            OH_PixelmapImageInfo_GetWidth(info, imageWidth);
            OH_PixelmapImageInfo_GetHeight(info, imageHeight);

            // set loaction parameters
            float realWidth = (float)*imageWidth, realHeight = (float)*imageHeight;
            float x1, x2, y1, y2;

            // calculate middle pointer offset
            float scaleX = width / realWidth, scaleY = height / realHeight;
            float scaleMin = scaleX < scaleY ? scaleX : scaleY;
            float scaleMax = scaleX > scaleY ? scaleX : scaleY;
            float scale = 0;
            if (align == "none") {
                x1 = 0, y1 = 0, x2 = realWidth * scaleMin, y2 = realHeight * scaleMin;
            } else {
                scale = (meetOrSlice == 1) ? scaleMax : scaleMin;
                float spaceX = width - realWidth * scale, spaceY = height - realHeight * scale;
                spaceX = spaceX / (2 * scale), spaceY = spaceY / (2 * scale);

                // preserveAspectRatio X define
                if (align.find("xMin") != std::string::npos) {
                    x1 = 0, x2 = realWidth + 2 * spaceX;
                }
                if (align.find("xMid") != std::string::npos) {
                    x1 = -spaceX, x2 = realWidth + spaceX;
                }
                if (align.find("xMax") != std::string::npos) {
                    x1 = -2 * spaceX, x2 = realWidth;
                }
                // preserveAspectRatio Y define
                if (align.find("YMin") != std::string::npos) {
                    y1 = 0, y2 = realHeight + 2 * spaceY;
                }
                if (align.find("YMid") != std::string::npos) {
                    y1 = -spaceY, y2 = realHeight + spaceY;
                }
                if (align.find("YMax") != std::string::npos) {
                    y1 = -2 * spaceY, y2 = realHeight;
                }
            }

            // set source Rect and destinaton Rect
            OH_Drawing_PixelMap *ohpixelmap = OH_Drawing_PixelMapGetFromOhPixelMapNative(pixelmap);
            drawing::Rect src(x1, y1, x2, y2);
            drawing::Rect dst(x, y, x + width, y + height);

            // draw the border of the area
            OH_Drawing_CanvasDrawLine(canvas, x, y, x + width, y);
            OH_Drawing_CanvasDrawLine(canvas, x + width, y, x + width, y + height);
            OH_Drawing_CanvasDrawLine(canvas, x + width, y + height, x, y + height);
            OH_Drawing_CanvasDrawLine(canvas, x, y + height, x, y);

            // set SamplingOptions
            OH_Drawing_FilterMode filterMode = FILTER_MODE_NEAREST;
            OH_Drawing_MipmapMode mipmapMode = MIPMAP_MODE_NONE;
            OH_Drawing_SamplingOptions *sampling = OH_Drawing_SamplingOptionsCreate(filterMode, mipmapMode);

            // Draw picture by type OH_Drawing_PixelMap
            OH_Drawing_CanvasDrawPixelMapRect(canvas, ohpixelmap, src.get(), dst.get(), sampling);

            // clear data
            OH_PixelmapImageInfo_Release(info);
            OH_Drawing_SamplingOptionsDestroy(sampling);
            OH_Drawing_PixelMapDissolve(ohpixelmap);
        }
        OH_ImageSourceNative_Release(res);
        OH_DecodingOptions_Release(options);
    }
}

} // namespace svg
} // namespace rnoh