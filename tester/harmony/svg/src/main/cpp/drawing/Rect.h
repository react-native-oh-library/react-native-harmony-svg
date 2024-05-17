#pragma once

#include <memory>
#include <native_drawing/drawing_rect.h>

namespace rnoh {
namespace drawing {
class Rect final {
    using UniqueNativeRect = std::unique_ptr<OH_Drawing_Rect, decltype(&OH_Drawing_RectDestroy)>;

public:
    Rect();
    Rect(float left, float top, float right, float bottom);
    Rect(Rect const &);
    Rect &operator=(Rect const &);
    Rect(Rect &&) = default;
    Rect &operator=(Rect &&) = default;
    ~Rect() noexcept = default;

    bool Intersect(const Rect &other);

    bool Join(const Rect &other);

    void SetLeft(float left);

    void SetTop(float top);

    void SetRight(float right);

    void SetBottom(float bottom);

    float GetLeft();

    float GetTop();

    float GetRight();

    float GetBottom();

    float GetHeight();

    float GetWidth();

    OH_Drawing_Rect *get() const { return rect_.get(); }

private:
    UniqueNativeRect rect_;
};
} // namespace drawing
} // namespace rnoh