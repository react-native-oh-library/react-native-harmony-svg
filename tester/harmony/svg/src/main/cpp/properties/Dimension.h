// from ArkUI "frameworks/base/geometry/dimension.h"
#pragma once
#include <cmath>
#include <string>
#include "Size.h"

#define NEAR_ZERO(value) ((value > 0.0) ? ((value - 0.0) <= 0.000001f) : ((0.0 - value) <= 0.000001f))

namespace rnoh {
enum class DimensionUnit {
    /*
     * Unit is invalid.
     */
    INVALID = -2,
    /*
     * Unit is empty.
     */
    NONE = -1,
    /*
     * Logical pixel used in Ace1.0. It's based on frontend design width.
     * For example, when a frontend with 750px design width running on a
     * device with 1080 pixels width, 1px represents 1.44 pixels.
     */
    PX = 0,
    /*
     * Density independent pixels, one vp is one pixel on a 160 dpi screen.
     */
    VP,
    /*
     * Scale independent pixels. This is like VP but will be scaled by
     * user's font size preference.
     */
    FP,
    /*
     * The percentage of either a value from the element's parent or from
     * another property of the element itself.
     */
    PERCENT,
    /*
     * logic pixels used in ACE2.0 instead of PX, and PX is the physical pixels in ACE2.0
     */
    LPX,
    /*
     * The value is calculated from the element's parent and another property of the element itself.
     */
    AUTO,
    /*
     * The value is expression.
     */
    CALC,
};

enum class SvgLengthType {
    HORIZONTAL,
    VERTICAL,
    OTHER,
};

/*
 * Dimension contains a value and an unit to represent different
 * scales in one class.
 */
class Dimension {
public:
    constexpr Dimension() = default;
    ~Dimension() = default;
    constexpr explicit Dimension(double value, DimensionUnit unit = DimensionUnit::PX) : value_(value), unit_(unit) {}

    void Reset() {
        value_ = 0.0;
        unit_ = DimensionUnit::PX;
    }

    void ResetInvalidValue() {
        if (std::isnan(value_)) {
            Reset();
        }
    }

    constexpr double Value() const { return value_; }

    void SetValue(double value) { value_ = value; }

    constexpr DimensionUnit Unit() const { return unit_; }

    void SetUnit(DimensionUnit unit) { unit_ = unit; }

    double ConvertToPx(double baseLen) const;

    double ConvertToPx(const Size &viewPort, SvgLengthType type) const;

    // Percentage unit conversion is not supported.
    double ConvertToVp() const {
        if (unit_ == DimensionUnit::VP) {
            return value_;
        }

//         auto pipeline = PipelineBase::GetCurrentContextSafely();
//         CHECK_NULL_RETURN(pipeline, 0.0);
//         if (unit_ == DimensionUnit::NONE) {
//             return value_ / pipeline->GetDipScale();
//         }
        if (unit_ == DimensionUnit::PX) {
            // TODO get densityPixels in CAPI
            return value_ / 3.25010318;
        }
//         if (unit_ == DimensionUnit::FP) {
//             return value_ * pipeline->GetFontScale();
//         }
//         if (unit_ == DimensionUnit::LPX) {
//             return value_ * pipeline->GetLogicScale() / pipeline->GetDipScale();
//         }
        return 0.0;
    };

    // Percentage unit conversion is not supported.
    double ConvertToPx() const {
        if (unit_ == DimensionUnit::NONE) {
            return value_;
        }
        if (unit_ == DimensionUnit::PX) {
            return value_;
        }

//         auto pipeline = PipelineBase::GetCurrentContextSafely();
//         CHECK_NULL_RETURN(pipeline, 0.0);
        if (unit_ == DimensionUnit::VP) {
            // TODO get densityPixels in CAPI
            return value_ * 3.25010318;
        }
        if (unit_ == DimensionUnit::FP) {
//             return value_ * pipeline->GetDipScale() * pipeline->GetFontScale();
            return value_ * 3.25010318;
        }
//         if (unit_ == DimensionUnit::LPX) {
//             return value_ * pipeline->GetLogicScale();
//         }
        return 0.0;
    };

    double GetNativeValue(DimensionUnit unit) const {
        if (unit_ == unit) {
            return value_;
        } else if (unit == DimensionUnit::PX) {
            return ConvertToPx();
        } else {
            return ConvertToVp();
        }
    }

    // support percentage unit conversion
    double ConvertToPxWithSize(double size) const;

    bool NormalizeToPx(double vpScale, double fpScale, double lpxScale, double parentLength, double &result) const;

    constexpr Dimension operator*(double value) const { return Dimension(value_ * value, unit_); }

    constexpr Dimension operator/(double value) const {
        // NearZero cannot be used in a constant expression
        if (NEAR_ZERO(value)) {
            return {};
        }
        return Dimension(value_ / value, unit_);
    }

    bool operator==(const Dimension &dimension) const {
        return (unit_ == dimension.unit_) && value_ == dimension.value_;
    }

    bool operator!=(const Dimension &dimension) const { return !operator==(dimension); }

    /*
     * Add two dimensions using the same unit.
     */
    constexpr Dimension operator+(const Dimension &dimension) const {
        if (NEAR_ZERO(dimension.Value())) {
            return *this;
        }
        return Dimension(value_ + dimension.value_, unit_);
    }

    /*
     * Add a new dimension to itself using same unit.
     */
    Dimension &operator+=(const Dimension &dimension) {
        value_ += dimension.value_;
        return *this;
    }

    /*
     * Minus a dimension using the same unit.
     */
    constexpr Dimension operator-(const Dimension &dimension) const {
        if (NEAR_ZERO(dimension.Value())) {
            return *this;
        }
        return Dimension(value_ - dimension.value_, unit_);
    }

    /*
     * The opposite of dimension.
     */
    constexpr Dimension operator-() const { return Dimension(-value_, unit_); }

    /*
     * Minus a dimension to itself using the same unit.
     */
    Dimension &operator-=(const Dimension &dimension) {
        value_ -= dimension.value_;
        return *this;
    }

    bool operator>(const Dimension &dimension) const { return (value_ > dimension.value_); }

    bool operator<(const Dimension &dimension) const { return (value_ < dimension.value_); }

    std::string ToString() const;

    static Dimension FromString(const std::string &str);

private:
    double value_ = 0.0;
    DimensionUnit unit_ = DimensionUnit::PX;
};

// literal operators for dimension
inline constexpr Dimension operator""_vp(long double value) {
    return Dimension(static_cast<double>(value), DimensionUnit::VP);
}

inline constexpr Dimension operator""_px(long double value) {
    return Dimension(static_cast<double>(value), DimensionUnit::PX);
}

inline constexpr Dimension operator""_fp(long double value) {
    return Dimension(static_cast<double>(value), DimensionUnit::FP);
}

inline constexpr Dimension operator""_pct(long double value) {
    return Dimension(static_cast<double>(value), DimensionUnit::PERCENT);
}

} // namespace rnoh