
#include "RNSVGSvgViewModule.h"
#include "SvgViewManager.h"

using namespace facebook;
using namespace react;

namespace rnoh {
namespace svg {

using Object = std::optional<jsi::Object>;

void RNSVGSvgViewModule::toDataURL(jsi::Runtime &rt, int32_t tag, Object options, std::function<void(std::string)>&& callback) {
    LOG(INFO) << "liwang----->[SVGTurboModule] toDataUrl IN! tag=" << tag;
    std::string base64 = "return base64 string from c++";
    auto svgSvg = SvgViewManager::getInstance().getSvgViewByTag(tag);
    if (svgSvg != nullptr) {
        //base64 = svgSvg->toDataURL(50, 50);
    }
    LOG(INFO) << "liwang----->[SVGTurboModule] base64=" << base64;
    jsInvoker_->invokeAsync([base64, endCallback = std::move(callback)] { endCallback(base64); });
    return;
}

static jsi::Value __hostFunction_RNSVGSvgViewModule_toDataURL(jsi::Runtime &rt, react::TurboModule &turboModule,
                                                              const jsi::Value *args, size_t count) {
    auto self = static_cast<RNSVGSvgViewModule *>(&turboModule);
    if (args[2].isObject()) {
        auto callback = std::make_shared<jsi::Function>(std::move(args[2].getObject(rt).getFunction(rt)));
        auto endCallback = [&rt, callback = std::move(callback)](std::string base64) {
            auto base64Value = jsi::String::createFromUtf8(rt, base64);
            callback->call(rt, {std::move(base64Value)});
        };
        static_cast<RNSVGSvgViewModule *>(&turboModule)
            ->toDataURL(rt, args[0].asNumber(), (args[1].isNull() || args[1].isUndefined())?Object(rt) : args[1].asObject(rt), std::move(endCallback));
        return jsi::Value::undefined();
    }
    static_cast<RNSVGSvgViewModule *>(&turboModule)->toDataURL(rt, args[0].asNumber(), 
        (args[1].isNull() || args[1].isUndefined())?Object(rt) : args[1].asObject(rt), [self, &rt](std::string base64) {});
    return jsi::Value::undefined();
}

RNSVGSvgViewModule::RNSVGSvgViewModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    { methodMap_["toDataURL"] = MethodMetadata{3, __hostFunction_RNSVGSvgViewModule_toDataURL}; };
}

} // namespace svg
} // namespace rnoh
