#pragma once
#include <unordered_map>
#include <vector>
#include "drawing/Path.h"
#include "drawing/Pen.h"
namespace drawing {
class GlyPathBag {
    private:
        int getIndex(char ch);
        std::vector<drawing::Path> paths;
        std::unordered_map<char, int> data;
        drawing::Pen paint;
    public:
        GlyPathBag(drawing::Pen const &paint) {
            // Make indexed-by-one, to allow zero to represent non-cached
            paths.push_back(drawing::Path());
        }
    drawing::Path getOrCreateAndCache(const char &ch, const std::string &current);
    
};
}

