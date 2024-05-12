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
    LOG(INFO) << "[SVGImageComponentInstance] x: " << x;
    LOG(INFO) << "[SVGImageComponentInstance] y: " << y;
    LOG(INFO) << "[SVGImageComponentInstance] width: " << width;
    LOG(INFO) << "[SVGImageComponentInstance] height: " << height;
    LOG(INFO) << "[SVGImageComponentInstance] opacity: " << opacity;
    LOG(INFO) << "[SVGImageComponentInstance] src: " << src.uri;
    
    // read imagesource from URI and Base64String
    // transform type from std::string to char*
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
    OH_Pixelmap_ImageInfo *info;
    OH_PixelmapImageInfo_Create(&info);
    OH_PixelmapNative_GetImageInfo(pixelmap, info);
    // get the resource properties: width and height
    uint32_t *imageWidth, *imageHeight;
    OH_PixelmapImageInfo_GetWidth(info, imageWidth);
    OH_PixelmapImageInfo_GetHeight(info, imageHeight);
    float realWidth = (float)*imageWidth, realHeight = (float)*imageHeight;
    float scaleX = width / realWidth,  scaleY = height / realHeight;
    float scale = scaleX < scaleY ? scaleX : scaleY;
    float spaceX = width - realWidth * scale, spaceY = height - realHeight * scale;
    spaceX /= 2, spaceY /= 2;
    // set source Rect and destinaton Rect
    OH_Drawing_PixelMap *ohpixelmap = OH_Drawing_PixelMapGetFromOhPixelMapNative(pixelmap);
    OH_Drawing_Rect *src = OH_Drawing_RectCreate(-spaceX, -spaceY, realWidth+spaceX, realHeight+spaceY);
    OH_Drawing_Rect *dst = OH_Drawing_RectCreate(x, y, x+width, y+height);
    
    // draw the border of the area
//     OH_Drawing_CanvasDrawLine(canvas, x, y, x + width, y);
//     OH_Drawing_CanvasDrawLine(canvas, x + width, y, x + width, y + height);
//     OH_Drawing_CanvasDrawLine(canvas, x + width, y + height, x, y + height);
//     OH_Drawing_CanvasDrawLine(canvas, x, y + height, x, y);
    
    // set SamplingOptions
    OH_Drawing_FilterMode filterMode = FILTER_MODE_NEAREST;
    OH_Drawing_MipmapMode mipmapMode = MIPMAP_MODE_NONE;
    OH_Drawing_SamplingOptions* sampling = OH_Drawing_SamplingOptionsCreate(filterMode, mipmapMode);
    
    // Draw picture by type OH_Drawing_PixelMap 
    OH_Drawing_CanvasDrawPixelMapRect(canvas, ohpixelmap, src, dst, sampling);

    OH_Drawing_RectDestroy(src);
    OH_Drawing_RectDestroy(dst);
    OH_Drawing_SamplingOptionsDestroy(sampling);
    delete[] uri;
}

} // namespace rnoh
