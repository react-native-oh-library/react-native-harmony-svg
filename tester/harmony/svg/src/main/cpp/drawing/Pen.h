#pragma once

#include <memory>
#include <native_drawing/drawing_pen.h>

namespace drawing {

class Pen final {

    using UniqueNativePen = std::unique_ptr<OH_Drawing_Pen, decltype(&OH_Drawing_PenDestroy)>;

public:
    using LineCapStyle = OH_Drawing_PenLineCapStyle;
    using LineJoinStyle = OH_Drawing_PenLineJoinStyle;

    Pen();

    Pen(Pen const &) = delete;
    Pen &operator=(Pen const &) = delete;

    Pen(Pen &&) = default;
    Pen &operator=(Pen &&) = default;

    ~Pen() noexcept = default;

    void SetAntiAlias(bool antiAlias);
    void SetColor(uint32_t color);
    void SetAlpha(uint8_t alpha);
    void SetWidth(double width);
    void SetMiterLimit(float miterLimit);
    void SetLineCap(LineCapStyle lineCap);
    void SetLineJoin(LineJoinStyle lineJoin);

    void Reset();

    OH_Drawing_Pen *get() const { return pen_.get(); }

private:
    UniqueNativePen pen_;
};

} // namespace drawing