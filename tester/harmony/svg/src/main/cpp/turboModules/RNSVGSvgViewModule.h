
#pragma once

#include <ReactCommon/TurboModule.h>
#include <react/bridging/Bridging.h>
#include "RNOH/ArkTSTurboModule.h"

using namespace facebook;

namespace rnoh {
namespace svg {

class JSI_EXPORT RNSVGSvgViewModule : public ArkTSTurboModule {
    using Object = std::optional<jsi::Object>;
public:
    RNSVGSvgViewModule(const ArkTSTurboModule::Context ctx, const std::string name);

    void toDataURL(jsi::Runtime& rt, int32_t tag, Object options, std::function<void(std::string)>&& callback);
};

} // namespace svg
} // namespace rnoh
