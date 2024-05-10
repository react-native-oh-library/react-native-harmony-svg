#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
namespace rnoh {
class SvgPath : public SvgGraphic {
public:
    SvgPath() = default;
    ~SvgPath() override = default;
    // onProps changed 进行修改
    std::string d;
    uint32_t colorFill;
    void OnDraw(OH_Drawing_Canvas *canvas) override;
    OH_Drawing_Path *AsPath() override;
private:
};

} // namespace rnoh