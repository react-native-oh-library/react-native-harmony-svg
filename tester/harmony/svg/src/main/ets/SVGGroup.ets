import { Descriptor, RNComponentFactory, ComponentBuilderContext } from '@ohos/rnoh'


export const SVG_GROUP_TYPE_NAME = "RNSVGGroup" as const

export type SVGGroupDescriptor = Descriptor<typeof SVG_GROUP_TYPE_NAME, any>


@Component
export struct SVGGroup {
  @Prop descriptor: SVGGroupDescriptor
  @BuilderParam buildCustomComponent: (ctx: ComponentBuilderContext) => void

  aboutToAppear() {
    console.log("RNOH::SVGGroup", JSON.stringify(this.descriptor))
  }

  build() {
    Shape() {
      ForEach(this.descriptor.childrenTags, (tag) => {
//        Text(JSON.stringify(this.ctx.descriptorRegistry.getDescriptor(tag))).fontColor("blue")
        RNComponentFactory({ tag: tag, buildCustomComponent: this.buildCustomComponent })
      }, tag => tag)
    }
    .width("100%")
    .height("100%")
    .position(this.descriptor
      .layoutMetrics.frame.origin)
    .backgroundColor("green")
    .borderWidth(1)
  }
}