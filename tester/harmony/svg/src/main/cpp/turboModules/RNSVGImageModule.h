#pragma once

#include <ReactCommon/TurboModule.h>
#include "RNOH/ArkTSTurboModule.h"

namespace rnoh {

class JSI_EXPORT RNSVGImageModule : public ArkTSTurboModule {
public:
    RNSVGImageModule(const ArkTSTurboModule::Context ctx, const std::string name);
};

} // namespace rnoh
