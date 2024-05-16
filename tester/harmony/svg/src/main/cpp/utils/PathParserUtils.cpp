//
// Created on 2024/5/16.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "PathParserUtils.h"

namespace rnoh {
namespace svg {

OH_Drawing_Path *PathParserUtils::parse(std::string d) {
    mPath = OH_Drawing_PathCreate();
    elements.clear();
    if (d.empty()) {
        return mPath;
    }
    char prev_cmd = ' ';
    l = d.length();
    s = d;
    i = 0;

    mPenX = 0;
    mPenY = 0;
    mPivotX = 0;
    mPivotY = 0;
    mPenDownX = 0;
    mPenDownY = 0;
    mPenDown = false;

    while (i < l) {
        skip_spaces();

        if (i >= l) {
            break;
        }

        bool has_prev_cmd = prev_cmd != ' ';
        char first_char = s[i];

        if (!has_prev_cmd && first_char != 'M' && first_char != 'm') {
            // The first segment must be a MoveTo.
            throw std::runtime_error("Unexpected character '" + std::string(1, first_char) +
                                     "' (i=" + std::to_string(i) + ", s=" + s + ")");
        }

        // TODO: simplify

        bool is_implicit_move_to;
        char cmd;

        if (is_cmd(first_char)) {
            is_implicit_move_to = false;
            cmd = first_char;
            i += 1;
        } else if (is_number_start(first_char) && has_prev_cmd) {
            if (prev_cmd == 'Z' || prev_cmd == 'z') {
                // ClosePath cannot be followed by a number.
                throw std::runtime_error("Unexpected number after 'z' (s=" + s + ")");
            }

            if (prev_cmd == 'M' || prev_cmd == 'm') {
                // 'If a moveto is followed by multiple pairs of coordinates,
                // the subsequent pairs are treated as implicit lineto commands.'
                // So we parse them as LineTo.
                is_implicit_move_to = true;
                cmd = is_absolute(prev_cmd) ? 'L' : 'l';
            } else {
                is_implicit_move_to = false;
                cmd = prev_cmd;
            }
        } else {
            throw std::runtime_error("Unexpected character '" + std::string(1, first_char) +
                                     "' (i=" + std::to_string(i) + ", s=" + s + ")");
        }

        bool absolute = is_absolute(cmd);
        switch (cmd) {
        case 'm': {
            move(parse_list_number(), parse_list_number());
            break;
        }
        case 'M': {
            moveTo(parse_list_number(), parse_list_number());
            break;
        }
        case 'l': {
            line(parse_list_number(), parse_list_number());
            break;
        }
        case 'L': {
            lineTo(parse_list_number(), parse_list_number());
            break;
        }
        case 'h': {
            line(parse_list_number(), 0);
            break;
        }
        case 'H': {
            lineTo(parse_list_number(), mPenY);
            break;
        }
        case 'v': {
            line(0, parse_list_number());
            break;
        }
        case 'V': {
            lineTo(mPenX, parse_list_number());
            break;
        }
        case 'c': {
            curve(parse_list_number(), parse_list_number(), parse_list_number(), parse_list_number(),
                  parse_list_number(), parse_list_number());
            break;
        }
        case 'C': {
            curveTo(parse_list_number(), parse_list_number(), parse_list_number(), parse_list_number(),
                    parse_list_number(), parse_list_number());
            break;
        }
        case 's': {
            smoothCurve(parse_list_number(), parse_list_number(), parse_list_number(), parse_list_number());
            break;
        }
        case 'S': {
            smoothCurveTo(parse_list_number(), parse_list_number(), parse_list_number(), parse_list_number());
            break;
        }
        case 'q': {
            quadraticBezierCurve(parse_list_number(), parse_list_number(), parse_list_number(), parse_list_number());
            break;
        }
        case 'Q': {
            quadraticBezierCurveTo(parse_list_number(), parse_list_number(), parse_list_number(), parse_list_number());
            break;
        }
        case 't': {
            smoothQuadraticBezierCurve(parse_list_number(), parse_list_number());
            break;
        }
        case 'T': {
            smoothQuadraticBezierCurveTo(parse_list_number(), parse_list_number());
            break;
        }
        case 'a': {
            arc(parse_list_number(), parse_list_number(), parse_list_number(), parse_flag(), parse_flag(),
                parse_list_number(), parse_list_number());
            break;
        }
        case 'A': {
            arcTo(parse_list_number(), parse_list_number(), parse_list_number(), parse_flag(), parse_flag(),
                  parse_list_number(), parse_list_number());
            break;
        }
        case 'z':
        case 'Z': {
            close();
            break;
        }
        default: {
            throw std::runtime_error("Unexpected command '" + std::string(1, cmd) + "' (s=" + s + ")");
        }
        }


        if (is_implicit_move_to) {
            if (absolute) {
                prev_cmd = 'M';
            } else {
                prev_cmd = 'm';
            }
        } else {
            prev_cmd = cmd;
        }
    }
    return mPath;
}
}
}