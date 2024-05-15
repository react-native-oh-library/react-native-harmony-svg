
#include "RNSVGRenderableModule.h"

// This file was generated.

namespace rnoh {
namespace svg {
using namespace facebook;

RNSVGRenderableModule::RNSVGRenderableModule(const ArkTSTurboModule::Context ctx, const std::string name) : ArkTSTurboModule(ctx, name) {
    methodMap_ = {
        ARK_METHOD_METADATA(isPointInFill, 2),
        ARK_METHOD_METADATA(isPointInStroke, 2),
        ARK_METHOD_METADATA(getTotalLength, 1),
        ARK_METHOD_METADATA(getPointAtLength, 2),
        ARK_METHOD_METADATA(getBBox, 2),
        ARK_METHOD_METADATA(getCTM, 1),
        ARK_METHOD_METADATA(getScreenCTM, 1),
        ARK_ASYNC_METHOD_METADATA(getRawResource, 1),
    };
}

} // namespace svg
} // namespace rnoh
