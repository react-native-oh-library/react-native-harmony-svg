#include "SvgRect.h"

namespace rnoh {
namespace svg {

drawing::Path SvgRect::AsPath() {
        LOG(INFO) << "[SvgRect] AsPath";
        //TODO implement ConvertDimensionToPx
        auto rect = OH_Drawing_RectCreate(vpToPx(x), vpToPx(y), vpToPx(x + width), vpToPx(y + height));
        auto roundRect = OH_Drawing_RoundRectCreate(rect,vpToPx(rx),vpToPx(ry));
        OH_Drawing_PathAddRoundRect(path_.get(), roundRect, PATH_DIRECTION_CW);
        return path_;
    };

} // namespace svg
} // namespace rnoh


