#pragma once
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_types.h>
#include <unordered_map>
#include <vector>
namespace drawing {
class GlyPathBag {
    private:
        int getIndex(char ch);
        std::vector<OH_Drawing_Path*> paths;
        std::unordered_map<char, int> data;
        OH_Drawing_Pen *paint;
    public:
        GlyPathBag(OH_Drawing_Pen *paint) {
            // Make indexed-by-one, to allow zero to represent non-cached
            paths.push_back(OH_Drawing_PathCreate());
        }
    OH_Drawing_Path* getOrCreateAndCache(const char &ch, const std::string &current);
    
};
}

