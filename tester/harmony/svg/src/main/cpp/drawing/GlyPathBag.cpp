#include "GlyPathBag.h"

int drawing::GlyPathBag::getIndex(char ch) {
    auto it = data.find(ch);
    return it == data.end() ? 0 : it->second;
}

drawing::Path drawing::GlyPathBag::getOrCreateAndCache(const char &ch, const std::string &current) {
    return drawing::Path();
}