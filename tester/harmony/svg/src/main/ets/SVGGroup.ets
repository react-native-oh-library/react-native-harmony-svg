import { Descriptor, RNComponentFactory, ComponentBuilderContext, convertColorValueToRGBA } from '@ohos/rnoh'


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
        RNComponentFactory({ tag: tag, buildCustomComponent: this.buildCustomComponent })
      }, tag => tag)
    }
    .width("100%")
    .height("100%")
    .position(this.descriptor.layoutMetrics.frame.origin)
    .strokeWidth(parseFloat(this.descriptor.props.strokeWidth ?? "0"))
    .stroke(this.descriptor.props.stroke?.payload ? convertColorValueToRGBA(this.descriptor.props.stroke?.payload) : undefined)
    .fill(this.descriptor.props.fill?.payload ? convertColorValueToRGBA(this.descriptor.props.fill?.payload) : undefined)
  }
}