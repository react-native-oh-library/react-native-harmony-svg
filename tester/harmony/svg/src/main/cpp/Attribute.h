// from ArkUI "frameworks/core/components/declaration/common/attribute.h"
#pragma once

namespace rnoh {

enum class AttributeTag {
    COMMON_ATTR = 0,
    COMMON_DISABLED_ATTR,
    COMMON_FOCUSABLE_ATTR,
    COMMON_TOUCHABLE_ATTR,
    COMMON_DATA_ATTR,
    COMMON_CLICK_EFFECT_ATTR,
    COMMON_RENDER_ATTR,
    COMMON_MULTIMODAL_ATTR,
    SPECIALIZED_ATTR,
    UNKNOWN,
    DEFAULT,
};

struct Attribute {
    bool IsValid() const { return tag != AttributeTag::UNKNOWN; }

    bool IsShared() const { return isShared; }

    bool isShared = true;
    AttributeTag tag = AttributeTag::DEFAULT;
};

}