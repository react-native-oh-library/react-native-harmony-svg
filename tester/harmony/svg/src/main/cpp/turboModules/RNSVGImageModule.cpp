#include "RNSVGImageModule.h"

using namespace rnoh;
using namespace facebook;

RNSVGImageModule::RNSVGImageModule(
    const ArkTSTurboModule::Context ctx,
    const std::string name)
    : ArkTSTurboModule(ctx, name) {
    methodMap_ = {
        ARK_ASYNC_METHOD_METADATA(getBase64String, 1),
    };
}