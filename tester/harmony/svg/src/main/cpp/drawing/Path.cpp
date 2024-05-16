#include "Path.h"


namespace rnoh::drawing {

Path::Path() : path_(UniqueNativePath(OH_Drawing_PathCreate(), &OH_Drawing_PathDestroy)) {}

Path::Path(Path const &other)
    : path_(UniqueNativePath(OH_Drawing_PathCopy(other.path_.get()), &OH_Drawing_PathDestroy)) {}

Path &Path::operator=(Path const &other) {
    if (this != &other) {
        path_ = UniqueNativePath(OH_Drawing_PathCopy(other.path_.get()), &OH_Drawing_PathDestroy);
    }
    return *this;
}

void Path::Reset() {
    OH_Drawing_PathReset(path_.get());
}

} // namespace rnoh::drawing