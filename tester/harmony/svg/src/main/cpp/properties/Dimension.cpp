#include "Dimension.h"
#include "Size.h"
namespace rnoh {
namespace svg {

double Dimension::RelativeConvertToPx(double baseLen, double scale) const {
    switch (Unit()) {
    case DimensionUnit::PERCENT: {
        return Value() * baseLen;
    }
    case DimensionUnit::PX:
        return Value();
    case DimensionUnit::VP:
        return ConvertToPx(scale);
    default:
        return ConvertToPx(scale);
    }
}

double Dimension::ConvertToPx(const Size &viewPort, SvgLengthType type, double scale) const {
    switch (type) {
    case SvgLengthType::HORIZONTAL: {
        return RelativeConvertToPx(viewPort.Width(), scale);
    }
    case SvgLengthType::VERTICAL:
        return RelativeConvertToPx(viewPort.Height(), scale);
    case SvgLengthType::OTHER:
        return RelativeConvertToPx(sqrt(viewPort.Width() * viewPort.Height()), scale);
    default:
        return 0.0;
    }
}

double Dimension::FromRelative(bool isObjectBoundingBoxUnit, double relative, double scale) {
    if (Unit() == DimensionUnit::PERCENT) {
        return Value() * relative;
    }
    double baseLen = isObjectBoundingBoxUnit ? relative : scale;
    return Value() * baseLen;
}
} // namespace svg
} // namespace rnoh