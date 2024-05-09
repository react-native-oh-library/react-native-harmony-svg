/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include "RNOH/CppComponentInstance.h"
// #include "SwiperNode.h"
// #include "EventEmitters.h"
#include <folly/dynamic.h>
#include <math.h>
#include "SvgArkUINode.h"
#include "ShadowNodes.h"
#include "SvgPattern.h"

namespace rnoh {
// 3.实现SvgCircleComponentInstance，继承SvgShadowNoder
class RNSVGPatternComponentInstance : public CppComponentInstance<facebook::react::RNSVGPatternShadowNode>, public SvgHost {

private:
    SvgArkUINode m_svgArkUINode;

public:
    // todo 构造SvgArkUINode 和SvgNode并把SvgNode设给SvgArkUINode
    RNSVGPatternComponentInstance(Context context);

    // 通过childComponentInstance拿到里面保存的SvgNode对象，设置给root
    void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override {
        OnChildInsertCommon(std::dynamic_pointer_cast<SvgHost>(childComponentInstance));
    }

    // 通过childComponentInstance拿到里面保存的SvgNode对象，从root_中删除
    void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override{}

    // 用来给父亲挂载节点
    SvgArkUINode &getLocalRootArkUINode() override;

    // 更新SvgNode中的属性
    void onPropsChanged(SharedConcreteProps const &props) override;

    // 处理标签上的方法，Svg可能不涉及，待确认是否需要支持
    void handleCommand(std::string const &commandName, folly::dynamic const &args) override{}

    // 分发Target事件，分发到svg下面的子节点；待确认是否需求要支持
//     std::vector<TouchTarget::Shared> getTouchTargetChildren() override
};
} // namespace rnoh