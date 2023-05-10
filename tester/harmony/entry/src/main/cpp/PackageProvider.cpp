#include "RNOH/PackageProvider.h"
#include "SVGPackage.h"

using namespace rnoh;

std::vector<std::shared_ptr<Package>> PackageProvider::getPackages(Package::Context ctx) {
    return {std::make_shared<SVGPackage>(ctx)};
}