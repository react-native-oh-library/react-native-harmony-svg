import { RNApp, ComponentBuilderContext, RNOHContext } from '@ohos/rnoh'
import {
  SVG_VIEW_TYPE_NAME,
  SVGView,
  SVGViewDescriptor,
  SVG_PATH_TYPE_NAME,
  SVGPath,
  SVGPathDescriptor,
  SVG_GROUP_TYPE_NAME,
  SVGGroup,
  SVGGroupDescriptor,
  SVGContainer
} from "@ohos/rnoh-svg"


let storage = LocalStorage.GetShared()

@Entry(storage)
@Component
struct Index {
  @LocalStorageProp('RNOHContext') rnohContext: RNOHContext | undefined = undefined

  @Builder
  buildCustomComponent(ctx: ComponentBuilderContext) {
    if (ctx.descriptor.type === SVG_VIEW_TYPE_NAME) {
      SVGContainer({
        ctx: ctx.rnohContext,
        tag: ctx.descriptor.tag,
      })
    }
    // } else if (ctx.descriptor.type === SVG_PATH_TYPE_NAME) {
    //   SVGPath({ ctx: ctx.rnohContext, descriptor: ctx.descriptor as SVGPathDescriptor })
    // } else if (ctx.descriptor.type === SVG_GROUP_TYPE_NAME) {
    //   SVGGroup({
    //     ctx: ctx.rnohContext,
    //     descriptor: ctx.descriptor as SVGGroupDescriptor,
    //     buildCustomComponent: this.buildCustomComponent.bind(this)
    //   })
    // }
  }

  build() {
    Column() {
      RNApp({
        rnohContext: this.rnohContext !,
        appName: "app_name",
        buildCustomComponent: this.buildCustomComponent.bind(this)
      })
    }
    .height('100%')
    .width('100%')
  }
}
