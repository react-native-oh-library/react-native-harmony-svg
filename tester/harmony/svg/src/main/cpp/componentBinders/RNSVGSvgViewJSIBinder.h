#pragma once

// This file was generated.

#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class RNSVGSvgViewJSIBinder : public ViewComponentJSIBinder {
  protected:
    facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
        auto object = ViewComponentJSIBinder::createNativeProps(rt);
        object.setProperty(rt, "bbWidth", true);
        object.setProperty(rt, "bbHeight", true);
        object.setProperty(rt, "minX", true);
        object.setProperty(rt, "minY", true);
        object.setProperty(rt, "vbWidth", true);
        object.setProperty(rt, "vbHeight", true);
        object.setProperty(rt, "align", true);
        object.setProperty(rt, "meetOrSlice", true);
        object.setProperty(rt, "tintColor", true);
        object.setProperty(rt, "color", true);
        object.setProperty(rt, "pointerEvents", true);
        return object;
    }

    facebook::jsi::Object createBubblingEventTypes(facebook::jsi::Runtime &rt) override {
        facebook::jsi::Object events(rt);
        return events;
    }

    facebook::jsi::Object createDirectEventTypes(facebook::jsi::Runtime &rt) override {
        facebook::jsi::Object events(rt);
        return events;
    }
};
} // namespace rnoh
