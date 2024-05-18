        
#pragma once

// This file was generated.
#pragma once

#include <ReactCommon/TurboModule.h>
#include <react/bridging/Bridging.h>
#include "RNOH/ArkTSTurboModule.h"
using namespace facebook;

namespace rnoh {
namespace svg {

class JSI_EXPORT RNSVGRenderableModule : public ArkTSTurboModule {
public:
    RNSVGRenderableModule(const ArkTSTurboModule::Context ctx, const std::string name);
    bool isPointInFill(jsi::Runtime &rt, int32_t tag, std::optional<jsi::Object> options);
    bool isPointInStroke(jsi::Runtime &rt, int32_t tag, std::optional<jsi::Object> options);
    double getTotalLength(jsi::Runtime &rt, int32_t tag);
    jsi::Object getPointAtLength(jsi::Runtime &rt, int32_t tag,std::optional<jsi::Object> options);
    jsi::Object getBBox(jsi::Runtime &rt, int32_t tag, std::optional<jsi::Object> options);
    jsi::Object getCTM(jsi::Runtime &rt, int32_t tag);
    jsi::Object getScreenCTM(jsi::Runtime &rt, int32_t tag);
    jsi::Value getRawResource(jsi::Runtime &rt, jsi::String name);
};

} // namespace svg
} // namespace rnoh
