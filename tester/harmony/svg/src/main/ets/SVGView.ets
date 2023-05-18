import { Descriptor, ComponentBuilderContext, RNComponentFactory, RNOHContext, convertColorValueToRGBA } from '@ohos/rnoh'

export const SVG_VIEW_TYPE_NAME = "RNSVGSvgView" as const

export type SVGViewDescriptor = Descriptor<typeof SVG_VIEW_TYPE_NAME, {
  backgroundColor?: number
}>



@Component
export struct SVGView {
  @Prop descriptor: SVGViewDescriptor
  @BuilderParam buildCustomComponent: (ctx: ComponentBuilderContext) => void
  @Consume("RNOHContext") ctx: RNOHContext

  build() {
    Shape() {
      ForEach(this.descriptor.childrenTags, (tag) => {
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
    .backgroundColor(this.descriptor.props.backgroundColor ? convertColorValueToRGBA(this.descriptor.props.backgroundColor) : undefined)
  }
}
