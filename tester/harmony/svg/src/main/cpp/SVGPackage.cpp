#include "SVGPackage.h"
#include "SVGComponentDescriptor.h"

using namespace rnoh;
using namespace facebook;

std::vector<react::ComponentDescriptorProvider> SVGPackage::createComponentDescriptorProviders() {
    return {react::concreteComponentDescriptorProvider<react::SVGComponentDescriptor>()};
}
