import { RNApp, ComponentBuilderContext, RNOHContext } from '@ohos/rnoh'
import { SVGContainer } from "@ohos/rnoh-svg"


let storage = LocalStorage.GetShared()

@Entry(storage)
@Component
struct Index {
  @LocalStorageProp('RNOHContext') rnohContext: RNOHContext | undefined = undefined

  @Builder
  buildCustomComponent(ctx: ComponentBuilderContext) {
    if (ctx.descriptor.type === SVGContainer.DESCRIPTOR_TYPE) {
      SVGContainer({
        ctx: ctx.rnohContext,
        tag: ctx.descriptor.tag,
      })
    }
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
