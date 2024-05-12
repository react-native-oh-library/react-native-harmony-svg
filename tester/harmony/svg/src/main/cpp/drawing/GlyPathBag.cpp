#include "GlyPathBag.h"

int drawing::GlyPathBag::getIndex(char ch) {
    auto it = data.find(ch);
    return it == data.end() ? 0 : it->second;
}

OH_Drawing_Path* drawing::GlyPathBag::getOrCreateAndCache(const char &ch, const std::string &current) {}