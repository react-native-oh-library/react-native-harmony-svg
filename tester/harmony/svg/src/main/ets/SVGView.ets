import { Descriptor, ComponentBuilderContext, RNComponentFactory, RNOHContext } from '@ohos/rnoh'

export const SVG_VIEW_TYPE_NAME = "RNSVGSvgView" as const

export type SVGViewDescriptor = Descriptor<typeof SVG_VIEW_TYPE_NAME, any>


@Component
export struct SVGView {
  @Prop descriptor: SVGViewDescriptor
  @BuilderParam buildCustomComponent: (ctx: ComponentBuilderContext) => void
  @Consume("RNOHContext") ctx: RNOHContext

  aboutToAppear() {
    console.log("RNOH::SVGView", JSON.stringify(this.descriptor))
  }

  build() {
    Shape() {
      ForEach(this.descriptor.childrenTags, (tag) => {
//        Text(JSON.stringify(this.ctx.descriptorRegistry.getDescriptor(tag))).fontColor("blue")
        RNComponentFactory({ tag: tag, buildCustomComponent: this.buildCustomComponent })
      }, tag => tag)
    }
    .width(this.descriptor
      .layoutMetrics
      .frame
      .size
      .width)
    .height(this.descriptor
      .layoutMetrics
      .frame
      .size
      .height)
    .position(this.descriptor
      .layoutMetrics.frame.origin)
    .backgroundColor("green")
    .borderWidth(1)
  }
}
