#include "RNOH/Package.h"

namespace rnoh {

class SVGPackage : public Package {
  public:
    SVGPackage(Package::Context ctx) : Package(ctx) {}

    std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override;
};
} // namespace rnoh