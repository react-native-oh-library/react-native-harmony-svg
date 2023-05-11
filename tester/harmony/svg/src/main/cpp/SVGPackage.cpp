#include "SVGPackage.h"
#include "RNSVGSvgViewComponentDescriptor.h"
#include "RNSVGGroupComponentDescriptor.h"
#include "RNSVGPathComponentDescriptor.h"

using namespace rnoh;
using namespace facebook;

std::vector<react::ComponentDescriptorProvider> SVGPackage::createComponentDescriptorProviders() {
    return {react::concreteComponentDescriptorProvider<react::RNSVGSvgViewComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGGroupComponentDescriptor>(),
            react::concreteComponentDescriptorProvider<react::RNSVGPathComponentDescriptor>()};
}
