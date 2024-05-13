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

namespace rnoh {
void SvgImage::OnDraw(OH_Drawing_Canvas *canvas) {
//     LOG(INFO) << "[SVGImageComponentInstance] x: " << x;
//     LOG(INFO) << "[SVGImageComponentInstance] y: " << y;
//     LOG(INFO) << "[SVGImageComponentInstance] width: " << width;
//     LOG(INFO) << "[SVGImageComponentInstance] height: " << height;
//     LOG(INFO) << "[SVGImageComponentInstance] opacity: " << opacity;
//     LOG(INFO) << "[SVGImageComponentInstance] src: " << src.uri;
//     meetOrSlice = "slice";
    LOG(INFO) << "[SVGImageComponentInstance] meetOrSlice: " << meetOrSlice;
    LOG(INFO) << "[SVGImageComponentInstance] align: " << align;
    
    // previous solution
    x = vpToPx(x), y = vpToPx(y), width = vpToPx(width), height = vpToPx(height);
    // read imagesource from URI and Base64String
    // transform type from std::string to char*
//     if (src.uri.find("base64") != std::string::npos) {
    if (src.uri.size() != 0) {
        OH_ImageSourceNative *res;
        OH_PixelmapNative *pixelmap;
        OH_DecodingOptions *options;
        
        int len = src.uri.size();
        char *uri = new char[len];
        for (int i = 0; i < len; i++) {
            uri[i] = src.uri[i];
        }
        OH_DecodingOptions_Create(&options);
        OH_ImageSourceNative_CreateFromUri(uri, len, &res);
        OH_ImageSourceNative_CreatePixelmap(res, options, &pixelmap);
        OH_PixelmapNative_Opacity(pixelmap, opacity);

        // get the real width and height from pixelmap(OH_PixelmapNative *)
        // return type uint32_t
        OH_Pixelmap_ImageInfo *info; // 1
        OH_PixelmapImageInfo_Create(&info);
        OH_PixelmapNative_GetImageInfo(pixelmap, info);
        
        // get the resource properties: width and height
        uint32_t *imageWidth;
        uint32_t *imageHeight;
        OH_PixelmapImageInfo_GetWidth(info, imageWidth);
        OH_PixelmapImageInfo_GetHeight(info, imageHeight);
        
        // set loaction parameters
        float realWidth = (float)*imageWidth, realHeight = (float)*imageHeight;
        float x1, x2, y1, y2;
        
        // calculate middle pointer offset
        float scaleX = width / realWidth,  scaleY = height / realHeight;
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
        OH_Drawing_Rect *src = OH_Drawing_RectCreate(x1, y1, x2, y2);
        OH_Drawing_Rect *dst = OH_Drawing_RectCreate(x, y, x + width, y + height);
        // draw the border of the area
//         OH_Drawing_CanvasDrawLine(canvas, x, y, x + width, y);
//         OH_Drawing_CanvasDrawLine(canvas, x + width, y, x + width, y + height);
//         OH_Drawing_CanvasDrawLine(canvas, x + width, y + height, x, y + height);
//         OH_Drawing_CanvasDrawLine(canvas, x, y + height, x, y);

        // set SamplingOptions
        OH_Drawing_FilterMode filterMode = FILTER_MODE_NEAREST;
        OH_Drawing_MipmapMode mipmapMode = MIPMAP_MODE_NONE;
        OH_Drawing_SamplingOptions* sampling = OH_Drawing_SamplingOptionsCreate(filterMode, mipmapMode);

        // Draw picture by type OH_Drawing_PixelMap 
        OH_Drawing_CanvasDrawPixelMapRect(canvas, ohpixelmap, src, dst, sampling);

        // clear data
        OH_ImageSourceNative_Release(res);
        OH_DecodingOptions_Release(options);
        OH_PixelmapImageInfo_Release(info);
        OH_Drawing_RectDestroy(src);
        OH_Drawing_RectDestroy(dst);
        OH_Drawing_SamplingOptionsDestroy(sampling);
        OH_Drawing_PixelMapDissolve(ohpixelmap);
        delete[] uri;
    }
}
} // namespace rnoh
