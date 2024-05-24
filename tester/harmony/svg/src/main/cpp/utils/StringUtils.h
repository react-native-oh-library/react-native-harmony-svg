// from ArkUI "frameworks/base/utils/string_utils.h"
#pragma once

#include <climits>
#include <cmath>
#include <codecvt>
#include <cstring>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include "Utils.h"
#include "properties/Dimension.h"
#include "utils/Utils.h"
// #include "pr"
// #include "pro"
// #include "base/geometry/calc_dimension.h"
// #include "base/geometry/dimension.h"
// #include "base/utils/linear_map.h"
// #include "base/utils/utils.h"

namespace rnoh {
namespace svg {

namespace StringUtils {
extern const char DEFAULT_STRING[];
extern const std::wstring DEFAULT_WSTRING;
extern const std::u16string DEFAULT_USTRING;
extern const std::u32string DEFAULT_U32STRING;
constexpr int32_t TEXT_CASE_LOWERCASE = 1;
constexpr int32_t TEXT_CASE_UPPERCASE = 2;
constexpr double PERCENT_VALUE = 100.0;
constexpr double DEGREES_VALUE = 360.0; // one turn means 360 deg
constexpr double GRADIANS_VALUE = 400.0; // one turn means 400 grad
constexpr double RADIANS_VALUE = 2 * M_PI; // one turn means 2*pi rad
const char ELLIPSIS[] = "...";


inline bool NotInUtf16Bmp(char16_t c)
{
    return (c & 0xF800) == 0xD800;
}

inline bool NotInBmp(wchar_t ch)
{
    return ch >= 0xD800 && ch <= 0xDBFF;
}

inline bool IsNumber(const std::string& value)
{
    if (value.empty()) {
        return false;
    }
    return std::all_of(value.begin(), value.end(), [](char i) { return isdigit(i); });
}

inline void ReplaceSpace(std::string& data)
{
    bool isFirstSpace = true;
    auto iter = data.begin();
    while (iter != data.end()) {
        if (*iter == ' ') {
            if (isFirstSpace) {
                iter++;
                isFirstSpace = false;
            } else {
                iter = data.erase(iter);
            }
        } else if (*iter == '\t') {
            *iter = ' ';
        } else {
            isFirstSpace = true;
            iter++;
        }
    }
}

inline void ReplaceTabAndNewLine(std::string& data)
{
    for (auto& i : data) {
        if (i == '\r' || i == '\n') {
            i = ' ';
        }
    }
    ReplaceSpace(data);
}

inline std::string RestoreEscape(const std::string& src)
{
    std::string res;
    for (auto &c : src) {
        switch (c) {
            case '\n':
                res += "\\n";
                break;
            case '\r':
                res += "\\r";
                break;
            case '\t':
                res += "\\t";
                break;
            default:
                res.push_back(c);
                break;
        }
    }
    return res;
}

inline int32_t StringToInt(const std::string& value)
{
    errno = 0;
    char* pEnd = nullptr;
    int64_t result = std::strtol(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || (result < INT_MIN || result > INT_MAX) || errno == ERANGE) {
        return 0;
    } else {
        return result;
    }
}

inline int64_t StringToLongInt(const std::string& value, int64_t defaultErr = 0)
{
    errno = 0;
    char* pEnd = nullptr;
    int64_t result = std::strtoll(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

inline uint64_t StringToLongUint(const std::string& value, uint64_t defaultErr = 0)
{
    errno = 0;
    char* pEnd = nullptr;
    uint64_t result = std::strtoull(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

inline uint32_t StringToUintCheck(const std::string& value, uint32_t defaultErr = 0)
{
    errno = 0;
    char* pEnd = nullptr;
    uint64_t result = std::strtoull(value.c_str(), &pEnd, 10);
    if ((pEnd == value.c_str()) || ((pEnd != nullptr) && (*pEnd != '\0')) || result > UINT32_MAX || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

inline uint32_t StringToUint(const std::string& value, uint32_t defaultErr = 0)
{
    errno = 0;
    char* pEnd = nullptr;
    uint64_t result = std::strtoull(value.c_str(), &pEnd, 10);
    if (pEnd == value.c_str() || result > UINT32_MAX || errno == ERANGE) {
        return defaultErr;
    } else {
        return result;
    }
}

// generic string to double value method without success check
inline double StringToDouble(const std::string& value)
{
    char* pEnd = nullptr;
    errno = 0;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return 0.0;
    } else {
        return result;
    }
}
// string to double method with success check, and support for parsing number string with percentage case
inline bool StringToDouble(const std::string& value, double& result)
{
    errno = 0;
    char* pEnd = nullptr;
    double res = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return false;
    } else if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            result = res / PERCENT_VALUE;
            return true;
        } else if (std::strcmp(pEnd, "") == 0) {
            result = res;
            return true;
        }
    }
    return false;
}

inline float StringToFloat(const std::string& value)
{
    errno = 0;
    char* pEnd = nullptr;
    float result = std::strtof(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return 0.0f;
    } else {
        return result;
    }
}

static Dimension FromString(const std::string &str) {
    static const int32_t percentUnit = 100;
    static const std::unordered_map<std::string, DimensionUnit> uMap{
        {"px", DimensionUnit::PX},     {"vp", DimensionUnit::VP},   {"fp", DimensionUnit::FP},
        {"%", DimensionUnit::PERCENT}, {"lpx", DimensionUnit::LPX}, {"auto", DimensionUnit::AUTO},
    };

    double value = 0.0;
    DimensionUnit unit = DimensionUnit::FP;

    if (str.empty()) {
        return Dimension(value, unit);
    }

    for (int32_t i = str.length() - 1; i >= 0; --i) {
        if (str[i] >= '0' && str[i] <= '9') {
            value = StringUtils::StringToDouble(str.substr(0, i + 1));
            auto subStr = str.substr(i + 1);
            unit = uMap.count(subStr) ? uMap.at(subStr) : unit;
            value = unit == DimensionUnit::PERCENT ? value / percentUnit : value;
            break;
        }
    }
    return Dimension(value, unit);
};

static Dimension StringToDimensionWithUnit(const std::string& value, DimensionUnit defaultUnit = DimensionUnit::PX,
    float defaultValue = 0.0f, bool isCalc = false)
{
    errno = 0;
    if (std::strcmp(value.c_str(), "auto") == 0) {
        return Dimension(defaultValue, DimensionUnit::AUTO);
    }
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return Dimension(defaultValue, defaultUnit);
    }
    if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            // Parse percent, transfer from [0, 100] to [0, 1]
            return Dimension(result / 100.0, DimensionUnit::PERCENT);
        }
        if (std::strcmp(pEnd, "px") == 0) {
            return Dimension(result, DimensionUnit::PX);
        }
        if (std::strcmp(pEnd, "vp") == 0) {
            return Dimension(result, DimensionUnit::VP);
        }
        if (std::strcmp(pEnd, "fp") == 0) {
            return Dimension(result, DimensionUnit::FP);
        }
        if (std::strcmp(pEnd, "lpx") == 0) {
            return Dimension(result, DimensionUnit::LPX);
        }
        if ((std::strcmp(pEnd, "\0") == 0) && isCalc) {
            return Dimension(result, DimensionUnit::NONE);
        }
        if (isCalc) {
            return Dimension(result, DimensionUnit::INVALID);
        }
    }
    return Dimension(result, defaultUnit);
}

// inline CalcDimension StringToCalcDimension(
//     const std::string& value, bool useVp = false, DimensionUnit defaultUnit = DimensionUnit::PX)
// {
//     if (value.find("calc") != std::string::npos) {
//         return CalcDimension(value, DimensionUnit::CALC);
//     } else {
//         if (useVp) {
//             return StringToDimensionWithUnit(value, DimensionUnit::VP);
//         }
//         return StringToDimensionWithUnit(value, defaultUnit);
//     }
// }

inline Dimension StringToDimension(const std::string& value, bool useVp = false)
{
    return StringToDimensionWithUnit(value, useVp ? DimensionUnit::VP : DimensionUnit::PX);
}

// inline Dimension StringToDimensionWithThemeValue(const std::string& value, bool useVp, const Dimension& themeValue)
// {
//     errno = 0;
//     char* pEnd = nullptr;
//     std::strtod(value.c_str(), &pEnd);
//     if (pEnd == value.c_str() || errno == ERANGE) {
//         return themeValue;
//     }
//
//     return StringToDimensionWithUnit(value, useVp ? DimensionUnit::VP : DimensionUnit::PX);
// }

static bool StringToDimensionWithUnitNG(const std::string& value, Dimension& dimensionResult,
    DimensionUnit defaultUnit = DimensionUnit::PX, float defaultValue = 0.0f, bool isCalc = false)
{
    errno = 0;
    if (std::strcmp(value.c_str(), "auto") == 0) {
        dimensionResult = Dimension(defaultValue, DimensionUnit::AUTO);
        return true;
    }
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        dimensionResult = Dimension(defaultValue, defaultUnit);
        return false;
    }
    if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            // Parse percent, transfer from [0, 100] to [0, 1]
            dimensionResult = Dimension(result / 100.0, DimensionUnit::PERCENT);
            return true;
        }
        if (std::strcmp(pEnd, "px") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::PX);
            return true;
        }
        if (std::strcmp(pEnd, "vp") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::VP);
            return true;
        }
        if (std::strcmp(pEnd, "fp") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::FP);
            return true;
        }
        if (std::strcmp(pEnd, "lpx") == 0) {
            dimensionResult = Dimension(result, DimensionUnit::LPX);
            return true;
        }
        if ((std::strcmp(pEnd, "\0") == 0) && isCalc) {
            dimensionResult = Dimension(result, DimensionUnit::NONE);
            return true;
        }
        if (isCalc) {
            dimensionResult = Dimension(result, DimensionUnit::INVALID);
            return true;
        }
        if ((std::strcmp(pEnd, "\0") != 0)) {
            dimensionResult = Dimension(result, DimensionUnit::NONE);
            return false;
        }
    }
    dimensionResult = Dimension(result, defaultUnit);
    return true;
}

// inline bool StringToCalcDimensionNG(
//     const std::string& value, CalcDimension& result, bool useVp = false,
//     DimensionUnit defaultUnit = DimensionUnit::PX)
// {
//     if (value.find("calc") != std::string::npos) {
//         result = CalcDimension(value, DimensionUnit::CALC);
//         return true;
//     } else {
//         return StringToDimensionWithUnitNG(value, result, useVp ? DimensionUnit::VP : defaultUnit);
//     }
// }

inline std::string ReplaceChar(std::string str, char old_char, char new_char)
{
    for (char& it : str) {
        if (it == old_char) {
            it = new_char;
        }
    }
    return str;
}

inline double StringToDegree(const std::string& value)
{
    // https://developer.mozilla.org/zh-CN/docs/Web/CSS/angle

    errno = 0;
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return 0.0;
    } else if (pEnd) {
        if ((std::strcmp(pEnd, "deg")) == 0) {
            return result;
        } else if (std::strcmp(pEnd, "grad") == 0) {
            return result / GRADIANS_VALUE * DEGREES_VALUE;
        } else if (std::strcmp(pEnd, "rad") == 0) {
            return result / RADIANS_VALUE * DEGREES_VALUE;
        } else if (std::strcmp(pEnd, "turn") == 0) {
            return result * DEGREES_VALUE;
        }
    }
    return StringToDouble(value);
}

// StringToDegree with check. If the string is valid, change result and return true, otherwise return false.
inline bool StringToDegree(const std::string& value, double& result)
{
    errno = 0;
    char* pEnd = nullptr;
    double temp = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return false;
    } else if (pEnd) {
        if (*pEnd == '\0') {
            result = temp;
            return true;
        }
        if (std::strcmp(pEnd, "deg") == 0) {
            result = temp;
            return true;
        }
        if (std::strcmp(pEnd, "grad") == 0) {
            result = temp / GRADIANS_VALUE * DEGREES_VALUE;
            return true;
        }
        if (std::strcmp(pEnd, "rad") == 0) {
            result = temp / RADIANS_VALUE * DEGREES_VALUE;
            return true;
        }
        if (std::strcmp(pEnd, "turn") == 0) {
            result = temp * DEGREES_VALUE;
            return true;
        }
    }
    return false;
}

template<class T>
inline void StringSplitter(
    const std::string& source, char delimiter, T (*func)(const std::string&), std::vector<T>& out)
{
    out.erase(out.begin(), out.end());

    if (source.empty()) {
        return;
    }

    std::size_t startIndex = 0;
    for (std::size_t index = 0; index < source.size(); index++) {
        if (source[index] != delimiter) {
            continue;
        }

        if (index > startIndex) {
            out.emplace_back(func(source.substr(startIndex, index - startIndex)));
        }
        startIndex = index + 1;
    }

    if (startIndex < source.size()) {
        out.emplace_back(func(source.substr(startIndex)));
    }
}

inline bool ParseStringToArray(const std::string& input, std::vector<float>& output)
{
    std::istringstream iss(StringUtils::ReplaceChar(input, ',', ' '));
    std::string token;

    while (iss >> token) {
        double value;
        if (!StringToDouble(token, value)) {
            return false;
        }
        output.emplace_back(value);
    }

    return true;
}

inline void StringSplitter(const std::string& source, char delimiter, std::vector<std::string>& out)
{
    using Func = std::string (*)(const std::string&);
    Func func = [](const std::string& value) { return value; };
    StringSplitter(source, delimiter, func, out);
}

inline void StringSplitter(const std::string& source, char delimiter, std::vector<double>& out)
{
    using Func = double (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToDouble(value); };
    StringSplitter(source, delimiter, func, out);
}

inline void StringSplitter(const std::string& source, char delimiter, std::vector<float>& out)
{
    using Func = float (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToFloat(value); };
    StringSplitter(source, delimiter, func, out);
}

inline void StringSplitter(const std::string& source, char delimiter, std::vector<int>& out)
{
    using Func = int32_t (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToInt(value); };
    StringSplitter(source, delimiter, func, out);
}

inline void StringSplitter(const std::string& source, char delimiter, std::vector<Dimension>& out)
{
    using Func = Dimension (*)(const std::string&);
    Func func = [](const std::string& value) { return StringToDimension(value); };
    StringSplitter(source, delimiter, func, out);
}

inline std::string DoubleToString(double value, int32_t precision = 2)
{
    std::ostringstream result;
    result.precision(precision);
    if (NearEqual(value, Infinity<double>())) {
        result << "Infinity";
    } else {
        result << std::fixed << value;
    }
    return result.str();
}

inline void DeleteAllMark(std::string& str, const char mark)
{
    str.erase(std::remove(str.begin(), str.end(), mark), str.end());
}

inline std::string TrimStr(const std::string& str, char cTrim = ' ')
{
    auto firstPos = str.find_first_not_of(cTrim);
    if (firstPos == std::string::npos) {
        return str;
    }
    auto endPos = str.find_last_not_of(cTrim);
    return str.substr(firstPos, endPos - firstPos + 1);
}

inline void TrimStrLeadingAndTrailing(std::string& str, char cTrim = ' ')
{
    auto firstIndexNotOfSpace = str.find_first_not_of(" ");
    if (firstIndexNotOfSpace == std::string::npos) {
        str = "";
        return;
    }
    str.erase(0, firstIndexNotOfSpace);
    auto lastIndexNotOfSpace = str.find_last_not_of(" ");
    if (lastIndexNotOfSpace == std::string::npos) {
        str = "";
        return;
    }
    str.erase(lastIndexNotOfSpace + 1);
}

inline void SplitStr(
    const std::string& str, const std::string& sep, std::vector<std::string>& out, bool needTrim = true)
{
    out.erase(out.begin(), out.end());

    if (str.empty() || sep.empty()) {
        return;
    }

    std::string strPart;
    std::string::size_type startPos = 0;
    std::string::size_type pos = str.find_first_of(sep, startPos);
    while (pos != std::string::npos) {
        if (pos > startPos) {
            strPart = needTrim ? TrimStr(str.substr(startPos, pos - startPos)) : str.substr(startPos, pos - startPos);
            out.emplace_back(std::move(strPart));
        }
        startPos = pos + sep.size();
        pos = str.find_first_of(sep, startPos);
    }

    if (startPos < str.size()) {
        strPart = needTrim ? TrimStr(str.substr(startPos)) : str.substr(startPos);
        out.emplace_back(std::move(strPart));
    }
}

inline void SplitStr(const std::string& str, const std::string& sep, std::vector<Dimension>& out, bool needTrim = true)
{
    out.erase(out.begin(), out.end());
    if (str.empty() || sep.empty()) {
        return;
    }
    std::string strPart;
    std::string::size_type startPos = 0;
    std::string::size_type pos = str.find_first_of(sep, startPos);
    while (pos != std::string::npos) {
        if (pos > startPos) {
            strPart = needTrim ? TrimStr(str.substr(startPos, pos - startPos)) : str.substr(startPos, pos - startPos);
            if (!strPart.empty()) {
                out.emplace_back(StringToDimension(std::move(strPart)));
            }
        }
        startPos = pos + sep.size();
        pos = str.find_first_of(sep, startPos);
    }
    if (startPos < str.size()) {
        strPart = needTrim ? TrimStr(str.substr(startPos)) : str.substr(startPos);
        if (!strPart.empty()) {
            out.emplace_back(StringToDimension(std::move(strPart)));
        }
    }
}

// const std::string ACE_EXPORT FormatString(const char* fmt, ...);

inline bool StartWith(const std::string& dst, const std::string& prefix)
{
    return dst.compare(0, prefix.size(), prefix) == 0;
}

inline bool StartWith(const std::string& str, const char* prefix, size_t prefixLen)
{
    return ((str.length() >= prefixLen) && (str.compare(0, prefixLen, prefix) == 0));
}

inline bool EndWith(const std::string& dst, const std::string& suffix)
{
    return (dst.size() >= suffix.size()) && dst.compare(dst.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline bool EndWith(const std::string& str, const char* suffix, size_t suffixLen)
{
    size_t len = str.length();
    return ((len >= suffixLen) && (str.compare(len - suffixLen, suffixLen, suffix) == 0));
}

inline void TransformStrCase(std::string& str, int32_t textCase)
{
    if (str.empty()) {
        return;
    }

    switch (textCase) {
        case TEXT_CASE_LOWERCASE:
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            break;
        case TEXT_CASE_UPPERCASE:
            transform(str.begin(), str.end(), str.begin(), ::toupper);
            break;
        default:
            break;
    }
}

bool IsAscii(const std::string& str);

inline std::vector<double> stringVectorToDoubleVector(const std::vector<std::string> &stringVec) {
    std::vector<double> doubleVec;
    doubleVec.reserve(stringVec.size()); // 预分配内存以提高效率
    for (const std::string &str : stringVec) {
            auto value = StringToDouble(str);
            doubleVec.push_back(vpToPx(value));
    }
    return doubleVec;
}

inline std::string doubleVectorToString(const std::vector<double>& doubleVec) {
    std::ostringstream oss;
    for (const double &num : doubleVec) {
            oss << num << ", "; // 将每个元素转换为字符串并拼接到流中
    }
    return oss.str(); // 将流中的内容转换为字符串并返回
}
}

} // namespace svg
} // namespace rnoh
