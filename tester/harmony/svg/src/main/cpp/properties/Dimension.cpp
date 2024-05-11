#include "Dimension.h"
#include "Size.h"
namespace rnoh {

double Dimension::ConvertToPx(double baseLen) const {
    switch (Unit()) {
    case DimensionUnit::PERCENT: {
        return Value() * baseLen;
    }
    case DimensionUnit::PX:
        return Value();
    case DimensionUnit::VP:
        return vpToPx(Value());
    default:
        return vpToPx(Value());
    }
}

double Dimension::ConvertToPx(const Size &viewPort, SvgLengthType type) const {
    switch (type) {
    case SvgLengthType::HORIZONTAL: {
        return ConvertToPx(viewPort.Width());
    }
    case SvgLengthType::VERTICAL:
        return ConvertToPx(viewPort.Height());
    case SvgLengthType::OTHER:
        return ConvertToPx(sqrt(viewPort.Width() * viewPort.Height()));
    default:
        return 0.0;
    }
}
} // namespace rnoh