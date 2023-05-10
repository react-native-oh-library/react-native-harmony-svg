#pragma once
#include <folly/dynamic.h>
#include <react/renderer/components/view/ViewProps.h>
#include <react/renderer/core/RawProps.h>

namespace facebook {
namespace react {

class SVGDynamicProps {
  public:
    SVGDynamicProps() {}

    SVGDynamicProps(const RawProps &rawProps) {
        m_dynamicProps = (folly::dynamic)rawProps;
    }

    folly::dynamic getDynamic() const {
        return m_dynamicProps;
    };

  private:
    folly::dynamic m_dynamicProps = folly::dynamic::object();
};

class SVGProps : public ViewProps, public SVGDynamicProps {
  public:
    SVGProps() {}

    SVGProps(const PropsParserContext &context, const SVGProps &sourceProps, const RawProps &rawProps)
        : ViewProps(context, sourceProps, rawProps),
          SVGDynamicProps(rawProps) {}
};

} // namespace react
} // namespace facebook