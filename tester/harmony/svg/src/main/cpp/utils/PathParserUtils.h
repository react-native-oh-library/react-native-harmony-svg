//
// Created on 2024/5/16.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_PATHPARSERUTILS_H
#define HARMONY_PATHPARSERUTILS_H
#pragma once
#include "SvgMarkerPositionUtils.h"
#include <cmath>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_types.h>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cctype>

namespace rnoh {
namespace svg {
    class PathParserUtils{
    
        public:
            float mScale;
            std::vector<PathElement> elements;
    
            OH_Drawing_Path *parse(std::string d);
    
        private:
            int i;
            int l;
            std::string s;
            OH_Drawing_Path *mPath;
            float mPenX, mPenY, mPenDownX, mPenDownY, mPivotX, mPivotY;
            bool mPenDown;
        
            void parse_list_separator() {
                if (i < l && s[i] == ',') {
                    i += 1;
                }
            }
        
            void skip_digits() {
                while (i < l && std::isdigit(s[i])) {
                    i++;
                }
            }
        
            void close() {
                if (mPenDown) {
                    mPenX = mPenDownX;
                    mPenY = mPenDownY;
                    mPenDown = false;
        //             OH_Drawing_PathClose(mPath);
                    elements.push_back(PathElement(ElementType::kCGPathElementCloseSubpath, {{mPenX, mPenY}}));
                }
            }
        
            void setPenDown() {
                if (!mPenDown) {
                  mPenDownX = mPenX;
                  mPenDownY = mPenY;
                  mPenDown = true;
                }
            }
        
            void moveTo(float x, float y) {
                mPenDownX = mPivotX = mPenX = x;
                mPenDownY = mPivotY = mPenY = y;
        //         OH_Drawing_PathMoveTo(mPath, x * mScale, y * mScale);
                elements.push_back(PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x, y)}));
            }
        
            void move(float x, float y) { moveTo(x + mPenX, y + mPenY); }
        
            void lineTo(float x, float y) {
                setPenDown();
                mPivotX = mPenX = x;
                mPivotY = mPenY = y;
        //         OH_Drawing_PathLineTo(mPath, x * mScale, y * mScale);
                elements.push_back(PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y)}));
            }
        
            void line(float x, float y) { lineTo(x + mPenX, y + mPenY); }
        
            void cubicTo(float c1x, float c1y, float c2x, float c2y, float ex, float ey) {
                setPenDown();
                mPenX = ex;
                mPenY = ey;
        //         OH_Drawing_PathCubicTo(mPath, c1x * mScale, c1y * mScale, c2x * mScale, c2y * mScale, ex * mScale, ey * mScale);
                elements.push_back(PathElement(ElementType::kCGPathElementAddCurveToPoint, {Point(c1x, c1y), Point(c2x, c2y), Point(ex, ey)}));
            }
        
            void curveTo(float c1x, float c1y, float c2x, float c2y, float ex, float ey) {
                mPivotX = c2x;
                mPivotY = c2y;
                cubicTo(c1x, c1y, c2x, c2y, ex, ey);
            }
        
            void curve(float c1x, float c1y, float c2x, float c2y, float ex, float ey) {
                curveTo(c1x + mPenX, c1y + mPenY, c2x + mPenX, c2y + mPenY, ex + mPenX, ey + mPenY);
            }
        
            void smoothCurveTo(float c1x, float c1y, float ex, float ey) {
                float c2x = c1x;
                float c2y = c1y;
                c1x = (mPenX * 2) - mPivotX;
                c1y = (mPenY * 2) - mPivotY;
                mPivotX = c2x;
                mPivotY = c2y;
                cubicTo(c1x, c1y, c2x, c2y, ex, ey);
            }
        
            void smoothCurve(float c1x, float c1y, float ex, float ey) {
                smoothCurveTo(c1x + mPenX, c1y + mPenY, ex + mPenX, ey + mPenY);
            }
        
            void quadraticBezierCurveTo(float c1x, float c1y, float c2x, float c2y) {
                mPivotX = c1x;
                mPivotY = c1y;
                float ex = c2x;
                float ey = c2y;
                c2x = (ex + c1x * 2) / 3;
                c2y = (ey + c1y * 2) / 3;
                c1x = (mPenX + c1x * 2) / 3;
                c1y = (mPenY + c1y * 2) / 3;
                cubicTo(c1x, c1y, c2x, c2y, ex, ey);
            }
            
            void quadraticBezierCurve(float c1x, float c1y, float c2x, float c2y) {
                quadraticBezierCurveTo(c1x + mPenX, c1y + mPenY, c2x + mPenX, c2y + mPenY);
            }
        
            void smoothQuadraticBezierCurveTo(float c1x, float c1y) {
                // FLog.w(ReactConstants.TAG, "smoothquad c1x: " + c1x + " c1y: " + c1y);
                float c2x = c1x;
                float c2y = c1y;
                c1x = (mPenX * 2) - mPivotX;
                c1y = (mPenY * 2) - mPivotY;
                quadraticBezierCurveTo(c1x, c1y, c2x, c2y);
            }
        
            void smoothQuadraticBezierCurve(float c1x, float c1y) {
                smoothQuadraticBezierCurveTo(c1x + mPenX, c1y + mPenY);
            }
        
            void arcToBezier(float cx, float cy, float rx, float ry, float sa, float ea, bool clockwise, float rad) {
                // Inverse Rotation + Scale Transform
                float cos = std::cos(rad);
                float sin = std::sin(rad);
                float xx = cos * rx;
                float yx = -sin * ry;
                float xy = sin * rx;
                float yy = cos * ry;
            
                // Bezier Curve Approximation
                float arc = ea - sa;
                if (arc < 0 && clockwise) {
                    arc += M_PI * 2;
                } else if (arc > 0 && !clockwise) {
                    arc -= M_PI * 2;
                }
            
                int n = static_cast<int>(std::ceil(std::abs(round(arc / (M_PI / 2)))));
            
                float step = arc / n;
                float k = (4.0f / 3.0f) * std::tan(step / 4);
            
                float x = std::cos(sa);
                float y = std::sin(sa);
            
                for (int i = 0; i < n; i++) {
                    float cp1x = x - k * y;
                    float cp1y = y + k * x;
            
                    sa += step;
                    x = std::cos(sa);
                    y = std::sin(sa);
            
                    float cp2x = x + k * y;
                    float cp2y = y - k * x;
            
                    float c1x = (cx + xx * cp1x + yx * cp1y);
                    float c1y = (cy + xy * cp1x + yy * cp1y);
                    float c2x = (cx + xx * cp2x + yx * cp2y);
                    float c2y = (cy + xy * cp2x + yy * cp2y);
                    float ex = (cx + xx * x + yx * y);
                    float ey = (cy + xy * x + yy * y);
            
                    // Assuming mPath is an instance of Path
        //             OH_Drawing_PathCubicTo(mPath, c1x * mScale, c1y * mScale, c2x * mScale, c2y * mScale, ex * mScale, ey * mScale);
                    elements.push_back(PathElement(ElementType::kCGPathElementMoveToPoint, {Point(c1x, c1y), Point(c2x, c2y), Point(ex, ey)}));
                }
            }
        
            void arcTo(float rx, float ry, float rotation, bool outer, bool clockwise, float x, float y) {
                float tX = mPenX;
                float tY = mPenY;
        
                ry = std::abs(ry == 0 ? (rx == 0 ? (y - tY) : rx) : ry);
                rx = std::abs(rx == 0 ? (x - tX) : rx);
        
                if (rx == 0 || ry == 0 || (x == tX && y == tY)) {
                    lineTo(x, y);
                    return;
                }
        
                float rad = static_cast<float>(std::atan2(y - tY, x - tX));
                float cos = std::cos(rad);
                float sin = std::sin(rad);
                x -= tX;
                y -= tY;
        
                // Ellipse Center
                float cx = cos * x / 2 + sin * y / 2;
                float cy = -sin * x / 2 + cos * y / 2;
                float rxry = rx * rx * ry * ry;
                float rycx = ry * ry * cx * cx;
                float rxcy = rx * rx * cy * cy;
                float a = rxry - rxcy - rycx;
        
                if (a < 0) {
                    a = std::sqrt(1 - a / rxry);
                    rx *= a;
                    ry *= a;
                    cx = x / 2;
                    cy = y / 2;
                } else {
                    a = std::sqrt(a / (rxcy + rycx));
        
                    if (outer == clockwise) {
                        a = -a;
                    }
                    float cxd = -a * cy * rx / ry;
                    float cyd = a * cx * ry / rx;
                    cx = cos * cxd - sin * cyd + x / 2;
                    cy = sin * cxd + cos * cyd + y / 2;
                }
        
                // Rotation + Scale Transform
                float xx = cos / rx;
                float yx = sin / rx;
                float xy = -sin / ry;
                float yy = cos / ry;
        
                // Start and End Angle
                float sa = static_cast<float>(std::atan2(xy * -cx + yy * -cy, xx * -cx + yx * -cy));
                float ea = static_cast<float>(std::atan2(xy * (x - cx) + yy * (y - cy), xx * (x - cx) + yx * (y - cy)));
        
                cx += tX;
                cy += tY;
                x += tX;
                y += tY;
        
                setPenDown();
        
                mPenX = mPivotX = x;
                mPenY = mPivotY = y;
        
                if (rx != ry || rad != 0.0f) {
                    arcToBezier(cx, cy, rx, ry, sa, ea, clockwise, rad);
                } else {
                    float start = sa;
                    float end = ea;
                    float sweep = fmodf(std::abs((start - end) * 180.0f / M_PI), 360.0f);
        
                    if (outer) {
                        if (sweep < 180) {
                            sweep = 360 - sweep;
                        }
                    } else {
                        if (sweep > 180) {
                            sweep = 360 - sweep;
                        }
                    }
        
                    if (!clockwise) {
                        sweep = -sweep;
                    }
                
                    // Assuming mPath is an instance of Path
        //             OH_Drawing_PathArcTo(mPath, (cx - rx) * mScale, (cy - rx) * mScale, (cx + rx) * mScale, (cy + rx) * mScale, start, sweep);
                    elements.push_back(PathElement(ElementType::kCGPathElementAddQuadCurveToPoint, {Point(x, y)}));
                }
            }
            
            void arc(float rx, float ry, float rotation, bool outer, bool clockwise, float x, float y) {
                arcTo(rx, ry, rotation, outer, clockwise, x + mPenX, y + mPenY);
            }
        
            double round(double val) {
                double multiplier = pow(10, 4);
                return round(val * multiplier) / multiplier;
            }
            
            void skip_spaces() {
                while (i < l && std::isspace(s[i])) i++;
            }
            
            bool is_cmd(char c) {
                switch (c) {
                    case 'M':
                    case 'm':
                    case 'Z':
                    case 'z':
                    case 'L':
                    case 'l':
                    case 'H':
                    case 'h':
                    case 'V':
                    case 'v':
                    case 'C':
                    case 'c':
                    case 'S':
                    case 's':
                    case 'Q':
                    case 'q':
                    case 'T':
                    case 't':
                    case 'A':
                    case 'a':
                        return true;
                }
                return false;
            }
        
            bool is_number_start(char c) {
                return (c >= '0' && c <= '9') || c == '.' || c == '-' || c == '+';
            }
            
            bool is_absolute(char c) {
                return std::isupper(c);
            }
        
            bool parse_flag() {
                skip_spaces();
            
                char c = s[i];
                switch (c) {
                    case '0':
                    case '1': {
                        i += 1;
                        if (i < l && s[i] == ',') {
                            i += 1;
                        }
                        skip_spaces();
                        break;
                    }
                    default:
                        throw std::runtime_error("Unexpected flag '" + std::string(1, c) + "' (i=" + std::to_string(i) + ", s=" + s + ")");
                }
            
                return c == '1';
            }
            
            
        
            float parse_number() {
                // Strip off leading whitespaces.
                skip_spaces();
            
                if (i == l) {
                    throw std::runtime_error("Unexpected end (s=" + s + ")");
                }
            
                int start = i;
            
                char c = s[i];
            
                // Consume sign.
                if (c == '-' || c == '+') {
                    i += 1;
                    c = s[i];
                }
            
                // Consume integer.
                if (c >= '0' && c <= '9') {
                    skip_digits();
                    if (i < l) {
                        c = s[i];
                    }
                } else if (c != '.') {
                    throw std::runtime_error("Invalid number formatting character '" + std::string(1, c) + "' (i=" + std::to_string(i) + ", s=" + s + ")");
                }
            
                // Consume fraction.
                if (c == '.') {
                    i += 1;
                    skip_digits();
                    if (i < l) {
                        c = s[i];
                    }
                }
            
                if ((c == 'e' || c == 'E') && i + 1 < l) {
                    char c2 = s[i + 1];
                    // Check for `em`/`ex`.
                    if (c2 != 'm' && c2 != 'x') {
                        i += 1;
                        c = s[i];
            
                        if (c == '+' || c == '-') {
                            i += 1;
                            skip_digits();
                        } else if (c >= '0' && c <= '9') {
                            skip_digits();
                        } else {
                            throw std::runtime_error("Invalid number formatting character '" + std::string(1, c) + "' (i=" + std::to_string(i) + ", s=" + s + ")");
                        }
                    }
                }
            
                std::string num = s.substr(start, i - start);
                float n = std::stof(num);
            
                // inf, nan, etc. are an error.
                if (std::isinf(n) || std::isnan(n)) {
                    throw std::runtime_error("Invalid number '" + num + "' (start=" + std::to_string(start) + ", i=" + std::to_string(i) + ", s=" + s + ")");
                }
            
                return n;
            }
        
            float parse_list_number() {
                if (i == l) {
                    throw std::runtime_error("Unexpected end s=(" + s + ")");
                }
        
                float n = parse_number();
                skip_spaces();
                parse_list_separator();
        
                return n;
            }
    };
}
}

#endif //HARMONY_PATHPARSERUTILS_H
