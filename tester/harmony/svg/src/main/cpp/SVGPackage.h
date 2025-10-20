/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNOH/Package.h"
#include <glog/logging.h>
#include "componentInstances/RNSVGForeignObjectComponentInstance.h"
#include "componentInstances/RNSVGSvgViewComponentInstance.h"
#include "componentInstances/RNSVGCircleComponentInstance.h"
#include "componentInstances/RNSVGGroupComponentInstance.h"
#include "componentInstances/RNSVGPathComponentInstance.h"
#include "componentInstances/RNSVGRectComponentInstance.h"
#include "componentInstances/RNSVGImageComponentInstance.h"
#include "componentInstances/RNSVGEllipseComponentInstance.h"
#include "componentInstances/RNSVGLinearGradientComponentInstance.h"
#include "componentInstances/RNSVGRadialGradientComponentInstance.h"
#include "componentInstances/RNSVGLineComponentInstance.h"
#include "componentInstances/RNSVGDefsComponentInstance.h"
#include "componentInstances/RNSVGTextComponentInstance.h"
#include "componentInstances/RNSVGTextPathComponentInstance.h"
#include "componentInstances/RNSVGTSpanComponentInstance.h"
#include "componentInstances/RNSVGClipPathComponentInstance.h"
#include "componentInstances/RNSVGMaskComponentInstance.h"
#include "componentInstances/RNSVGUseComponentInstance.h"
#include "componentInstances/RNSVGMarkerComponentInstance.h"
#include "componentInstances/RNSVGPatternComponentInstance.h"
#include "componentInstances/RNSVGSymbolComponentInstance.h"
using namespace rnoh;
using namespace facebook;
using namespace svg;

namespace rnoh {

class SVGPackageComponentInstanceFactoryDelegate : public ComponentInstanceFactoryDelegate {
public:
    using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;

    ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
        DLOG(INFO) << "[SVGPackageComponentInstanceFactoryDelegate] create componentName= " << ctx.componentName;
        if (ctx.componentName == "RNSVGSvgView") {
            return std::make_shared<RNSVGSvgViewComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGForeignObject") {
           return std::make_shared<RNSVGForeignObjectComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGCircle") {
            return std::make_shared<RNSVGCircleComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGGroup") {
            return std::make_shared<RNSVGGroupComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGPath") {
            return std::make_shared<RNSVGPathComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGRect") {
            return std::make_shared<RNSVGRectComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGImage") {
            return std::make_shared<RNSVGImageComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGEllipse") {
            return std::make_shared<RNSVGEllipseComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGLinearGradient") {
            return std::make_shared<RNSVGLinearGradientComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGRadialGradient") {
            return std::make_shared<RNSVGRadialGradientComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGLine") {
            return std::make_shared<RNSVGLineComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGDefs") {
            return std::make_shared<RNSVGDefsComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGText") {
            return std::make_shared<RNSVGTextComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGTSpan") {
            return std::make_shared<RNSVGTSpanComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGTextPath") {
            return std::make_shared<RNSVGTextPathComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGClipPath") {
            return std::make_shared<RNSVGClipPathComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGMask") {
            return std::make_shared<RNSVGMaskComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGUse") {
            return std::make_shared<RNSVGUseComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGMarker") {
            return std::make_shared<RNSVGMarkerComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGPattern") {
            return std::make_shared<RNSVGPatternComponentInstance>(std::move(ctx));
        }
        if (ctx.componentName == "RNSVGSymbol") {
            return std::make_shared<RNSVGSymbolComponentInstance>(std::move(ctx));
        }
        return nullptr;
    }
};

class SVGPackage : public Package {
public:
    explicit SVGPackage(Package::Context ctx) : Package(ctx) {}

    std::unique_ptr<TurboModuleFactoryDelegate> createTurboModuleFactoryDelegate() override;

    ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override {
        return std::make_shared<SVGPackageComponentInstanceFactoryDelegate>();
    }

    std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override;

    ComponentNapiBinderByString createComponentNapiBinderByName() override;

    ComponentJSIBinderByString createComponentJSIBinderByName() override;
};

} // namespace rnoh