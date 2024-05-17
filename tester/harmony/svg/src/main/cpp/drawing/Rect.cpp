#include "Rect.h"

namespace rnoh {
namespace drawing {
Rect::Rect() : Rect(0, 0, 0, 0) {}

Rect::Rect(float left, float top, float right, float bottom) : rect_(UniqueNativeRect(OH_Drawing_RectCreate(left, top, right, bottom), &OH_Drawing_RectDestroy)) {}

Rect::Rect(Rect const &other) : Rect() {
    *this = other;
}
Rect &Rect::operator=(Rect const &other) {
    OH_Drawing_RectCopy(other.get(), get());
    return *this;
}

bool Rect::Intersect(const Rect &other) {
    return OH_Drawing_RectIntersect(get(), other.get());
}

bool Rect::Join(const Rect &other) {
    return OH_Drawing_RectJoin(get(), other.get());
}

void Rect::SetLeft(float left) {
    OH_Drawing_RectSetLeft(get(), left);
}

void Rect::SetTop(float top) {
    OH_Drawing_RectSetTop(get(), top);
}

void Rect::SetRight(float right) {
    OH_Drawing_RectSetRight(get(), right);
}

void Rect::SetBottom(float bottom) {
    OH_Drawing_RectSetBottom(get(), bottom);
}

float Rect::GetLeft() {
    return OH_Drawing_RectGetLeft(get());
}

float Rect::GetTop() {
    return OH_Drawing_RectGetTop(get());
}

float Rect::GetRight() {
    return OH_Drawing_RectGetRight(get());
}

float Rect::GetBottom() {
    return OH_Drawing_RectGetBottom(get());
}

float Rect::GetHeight() {
    return OH_Drawing_RectGetHeight(get());
}

float Rect::GetWidth() {
    return OH_Drawing_RectGetWidth(get());
}

} // namespace drawing
} // namespace rnoh