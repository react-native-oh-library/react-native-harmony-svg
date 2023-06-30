#include "SVGPackage.h"
#include "RNSVGSvgViewComponentDescriptor.h"
#include "RNSVGGroupComponentDescriptor.h"
#include "RNSVGPathComponentDescriptor.h"
#include "RNSVGRectComponentDescriptor.h"
#include "RNSVGCircleComponentDescriptor.h"
#include "RNSVGDefsComponentDescriptor.h"
#include "RNSVGClipPathComponentDescriptor.h"
#include "RNSVGImageComponentDescriptor.h"

using namespace rnoh;
using namespace facebook;

std::vector<react::ComponentDescriptorProvider> SVGPackage::createComponentDescriptorProviders() {
    return {react::concreteComponentDescriptorProvider<react::RNSVGSvgViewComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGGroupComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGPathComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGCircleComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGDefsComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGClipPathComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGImageComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGRectComponentDescriptor>()};
}
