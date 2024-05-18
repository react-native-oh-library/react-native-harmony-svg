#pragma once

// This file was generated.

#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class RNSVGTSpanJSIBinder : public ViewComponentJSIBinder {
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
        object.setProperty(rt, "fill", "Object");
        object.setProperty(rt, "fillOpacity", true);
        object.setProperty(rt, "fillRule", true);
        object.setProperty(rt, "stroke", "Object");
        object.setProperty(rt, "strokeOpacity", true);
        object.setProperty(rt, "strokeWidth", true);
        object.setProperty(rt, "strokeLinecap", true);
        object.setProperty(rt, "strokeLinejoin", true);
        object.setProperty(rt, "strokeDasharray", true);
        object.setProperty(rt, "strokeDashoffset", true);
        object.setProperty(rt, "strokeMiterlimit", true);
        object.setProperty(rt, "vectorEffect", true);
        object.setProperty(rt, "propList", true);
        object.setProperty(rt, "fontSize", true);
        object.setProperty(rt, "fontWeight", true);
        object.setProperty(rt, "font", "Object");
        object.setProperty(rt, "dx", true);
        object.setProperty(rt, "dy", true);
        object.setProperty(rt, "x", true);
        object.setProperty(rt, "y", true);
        object.setProperty(rt, "rotate", true);
        object.setProperty(rt, "inlineSize", true);
        object.setProperty(rt, "textLength", true);
        object.setProperty(rt, "baselineShift", true);
        object.setProperty(rt, "lengthAdjust", true);
        object.setProperty(rt, "alignmentBaseline", true);
        object.setProperty(rt, "verticalAlign", true);
        object.setProperty(rt, "content", true);
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
