#pragma once

// This file was generated.

#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class RNSVGRadialGradientJSIBinder : public ViewComponentJSIBinder {
  protected:
    facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
        auto object = ViewComponentJSIBinder::createNativeProps(rt);
        object.setProperty(rt, "name", true);
        object.setProperty(rt, "opacity", true);
        object.setProperty(rt, "matrix", true);
        object.setProperty(rt, "mask", true);
        object.setProperty(rt, "markerStart", true);
        object.setProperty(rt, "markerMid", true);
        object.setProperty(rt, "markerEnd", true);
        object.setProperty(rt, "clipPath", true);
        object.setProperty(rt, "clipRule", true);
        object.setProperty(rt, "responsible", true);
        object.setProperty(rt, "display", true);
        object.setProperty(rt, "pointerEvents", true);
        object.setProperty(rt, "fx", true);
        object.setProperty(rt, "fy", true);
        object.setProperty(rt, "cx", true);
        object.setProperty(rt, "cy", true);
        object.setProperty(rt, "rx", true);
        object.setProperty(rt, "ry", true);
        object.setProperty(rt, "gradient", true);
        object.setProperty(rt, "gradientUnits", true);
        object.setProperty(rt, "gradientTransform", true);
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
