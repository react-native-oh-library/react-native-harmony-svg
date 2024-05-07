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

#include "SvgPath.h"

namespace rnoh {

std::vector<std::string> split_string(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void SvgPath::OnDraw(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[SVGPath] OnDraw:";
    //     auto brush = OH_Drawing_BrushCreate();
    //     OH_Drawing_BrushSetColor(brush, 0xffffc0cb);
    //
    //     OH_Drawing_CanvasAttachBrush(canvas, brush);
    //     auto point = OH_Drawing_PointCreate(x, y);
    //     // 使用 props属性生成路径。
    //     OH_Drawing_CanvasDrawCircle(canvas, point, r);
    //     OH_Drawing_PointDestroy(point);
}


OH_Drawing_Path *SvgPath::AsPath() {
    LOG(INFO) << "[SVGPath] AsPath:";
    auto path = OH_Drawing_PathCreate();
    
    std::vector<std::string> words = split_string(d, ' ');
    for (int i = 0; i < words.size(); ++i)
        if (!words.empty()) { // 确保字符串不为空
            LOG(INFO) << "[SVGPath] words:" << words[i];
            char firstChar = words[i].at(0); // 使用索引操作符获取第一个字符
            LOG(INFO) << "[SVGPath] firstChar:" << firstChar;
            if (firstChar == 'M') {
                // 在给定的 (x, y) 坐标处开始一个新的子路径。
               // OH_Drawing_PathMoveTo (path , float x, float y )
            }
            if (firstChar == 'L') {
                // 从当前点到给定的 (x, y) 坐标画一条线，该坐标成为新的当前点。
            }
            if (firstChar == 'H') {
                // 从当前点绘制一条水平线，等效于将y坐标指定为0的L命令。
            }
            if (firstChar == 'V') {
                // 从当前点绘制一条垂直线，等效于将x坐标指定为0的L命令。
            }
            if (firstChar == 'C') {
                // 使用 (x1, y1) 作为曲线起点的控制点， (x2, y2) 作为曲线终点的控制点，从当前点到 (x, y)
                // 绘制三次贝塞尔曲线。
            }
            if (firstChar == 'S') {
                //(x2, y2) 作为曲线终点的控制点，绘制从当前点到 (x, y) 绘制三次贝塞尔曲线。
            }
            if (firstChar == 'Q') {
                // 使用 (x1, y1) 作为控制点，从当前点到 (x, y) 绘制二次贝塞尔曲线。
            }
            if (firstChar == 'T') {
                // 绘制从当前点到 (x, y) 绘制二次贝塞尔曲线。
            }
            if (firstChar == 'A') {
                // 从当前点到 (x, y) 绘制一条椭圆弧。
            }
            if (firstChar == 'Z') {
                // 通过将当前路径连接回当前子路径的初始点来关闭当前子路径。
            }
        }
    //
    //    //  OH_Drawing_PathClose(path);
          return path;
    //
    //
}


} // namespace rnoh
