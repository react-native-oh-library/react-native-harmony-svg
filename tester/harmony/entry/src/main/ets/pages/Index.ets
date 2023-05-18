import { RNApp, RNInstance, ComponentBuilderContext, RNOHContext } from '@ohos/rnoh'
import {
  SVG_VIEW_TYPE_NAME,
  SVGView,
  SVGViewDescriptor,
  SVG_PATH_TYPE_NAME,
  SVGPath,
  SVGPathDescriptor,
  SVG_GROUP_TYPE_NAME,
  SVGGroup,
  SVGGroupDescriptor
} from "@ohos/rnoh-svg"


@Entry
@Component
struct Index {
  @Provide("RNOHContext") rnohContext: RNOHContext = new RNOHContext();

  @Builder
  buildCustomComponent(ctx: ComponentBuilderContext) {
    if (ctx.descriptor.type === SVG_VIEW_TYPE_NAME) {
      SVGView({ descriptor: ctx.descriptor as SVGViewDescriptor, buildCustomComponent: this.buildCustomComponent.bind(this) })
    } else if (ctx.descriptor.type === SVG_PATH_TYPE_NAME) {
      SVGPath({ descriptor: ctx.descriptor as SVGPathDescriptor })
    } else if (ctx.descriptor.type === SVG_GROUP_TYPE_NAME) {
      SVGGroup({ descriptor: ctx.descriptor as SVGGroupDescriptor, buildCustomComponent: this.buildCustomComponent.bind(this) })
    }
  }

  build() {
    Column() {
      RNApp({
        rnInstance: new RNInstance("", (ctx) => []),
        buildCustomComponent: this.buildCustomComponent.bind(this),
      })
    }
    .height('100%')
    .width('100%')
  }
}
