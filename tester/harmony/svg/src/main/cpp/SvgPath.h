#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
namespace rnoh {
class SvgPath : public SvgGraphic {
public:
    SvgPath() = default;
    ~SvgPath() override = default;
    
    std::string d;
    
    OH_Drawing_Path *AsPath() override;
};

} // namespace rnoh