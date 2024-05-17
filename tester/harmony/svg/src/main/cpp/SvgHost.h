#pragma once

#include <memory>
#include "SvgNode.h"
namespace rnoh {
namespace svg {

class SvgHost {
 public:
     SvgHost() = default;
     virtual ~SvgHost() = default;
     void SetSvgNode(const std::shared_ptr<SvgNode> &svgNode) { m_svgNode = svgNode; };
     const std::shared_ptr<SvgNode> &GetSvgNode() { return m_svgNode; };

     void OnChildInsertCommon(const std::shared_ptr<SvgHost> &childSvgHost);

     void OnChildRemoveCommon(const std::shared_ptr<SvgHost> &childSvgHost);

 private:
  std::shared_ptr<SvgNode> m_svgNode;
};

} // namespace svg
} // namespace rnoh