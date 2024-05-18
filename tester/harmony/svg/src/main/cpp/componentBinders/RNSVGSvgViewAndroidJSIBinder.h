#pragma once

// This file was generated.

#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class RNSVGSvgViewAndroidJSIBinder : public ViewComponentJSIBinder {
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
        object.setProperty(rt, "hasTVPreferredFocus", true);
        object.setProperty(rt, "borderTopEndRadius", true);
        object.setProperty(rt, "borderBottomStartRadius", true);
        object.setProperty(rt, "borderBottomColor", true);
        object.setProperty(rt, "nextFocusDown", true);
        object.setProperty(rt, "borderRightColor", true);
        object.setProperty(rt, "nextFocusRight", true);
        object.setProperty(rt, "borderLeftColor", true);
        object.setProperty(rt, "borderColor", true);
        object.setProperty(rt, "removeClippedSubviews", true);
        object.setProperty(rt, "nextFocusForward", true);
        object.setProperty(rt, "nextFocusUp", true);
        object.setProperty(rt, "accessible", true);
        object.setProperty(rt, "borderStartColor", true);
        object.setProperty(rt, "borderBottomEndRadius", true);
        object.setProperty(rt, "borderEndColor", true);
        object.setProperty(rt, "focusable", true);
        object.setProperty(rt, "nativeBackgroundAndroid", "Object");
        object.setProperty(rt, "borderTopStartRadius", true);
        object.setProperty(rt, "nativeForegroundAndroid", "Object");
        object.setProperty(rt, "backfaceVisibility", true);
        object.setProperty(rt, "borderStyle", true);
        object.setProperty(rt, "needsOffscreenAlphaCompositing", true);
        object.setProperty(rt, "hitSlop", "Object");
        object.setProperty(rt, "borderTopColor", true);
        object.setProperty(rt, "nextFocusLeft", true);
        object.setProperty(rt, "borderTopRightRadius", true);
        object.setProperty(rt, "borderBottomRightRadius", true);
        object.setProperty(rt, "borderRadius", true);
        object.setProperty(rt, "borderBottomLeftRadius", true);
        object.setProperty(rt, "borderTopLeftRadius", true);
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
