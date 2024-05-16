#pragma once

#include <memory>
#include <native_drawing/drawing_brush.h>

namespace drawing {

class Brush final {

    using UniqueNativeBrush = std::unique_ptr<OH_Drawing_Brush, decltype(&OH_Drawing_BrushDestroy)>;

public:
    Brush();

    Brush(Brush const &) = delete;
    Brush &operator=(Brush const &) = delete;

    Brush(Brush &&) = default;
    Brush &operator=(Brush &&) = default;

    ~Brush() noexcept = default;

    void SetAntiAlias(bool antiAlias);
    void SetColor(uint32_t color);
    void SetAlpha(uint8_t alpha);

    void Reset();

    OH_Drawing_Brush *get() const { return brush_.get(); }

private:
    UniqueNativeBrush brush_;
};

} // namespace drawing