#include "GlyPathBag.h"
#include "Path.h"

namespace rnoh::drawing {


int GlyPathBag::getIndex(char ch) {
    auto it = data.find(ch);
    return it == data.end() ? 0 : it->second;
}

drawing::Path GlyPathBag::getOrCreateAndCache(const char &ch, const std::string &current) {
    return drawing::Path();
}

} // namespace rnoh::drawing