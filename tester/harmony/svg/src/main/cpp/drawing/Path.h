#pragma once

#include <memory>
#include <native_drawing/drawing_path.h>

namespace drawing {

class Path final {
    using UniqueNativePath = std::unique_ptr<OH_Drawing_Path, decltype(&OH_Drawing_PathDestroy)>;

public:
    Path();

    Path(Path const &);
    Path &operator=(Path const &);

    Path(Path &&) = default;
    Path &operator=(Path &&) = default;

    ~Path() noexcept = default;

    void Reset();

    OH_Drawing_Path *get() const { return path_.get(); }

private:
    UniqueNativePath path_;
};

} // namespace drawing