import { RNApp, RNInstance, ComponentBuilderContext } from '@ohos/rnoh'
import { SVG_TYPE_NAME, SVG, SVGDescriptor } from "@ohos/rnoh-svg"

@Entry
@Component
struct Index {
  @Builder
  buildCustomComponent(ctx: ComponentBuilderContext) {
//    if (ctx.descriptor.type === SVG_TYPE_NAME) {
//      SVG({ descriptor: ctx.descriptor as SVGDescriptor })
//    }
  }

  build() {
    Column() {
      RNApp({
        rnInstance: new RNInstance((ctx) => []),
        buildCustomComponent: this.buildCustomComponent,
      })
    }
    .height('100%')
    .width('100%')
  }
}
