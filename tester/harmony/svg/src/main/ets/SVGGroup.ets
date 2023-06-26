import { Descriptor, RNComponentFactory, ComponentBuilderContext, convertColorValueToRGBA, RNOHContext } from '@ohos/rnoh'


export const SVG_GROUP_TYPE_NAME = "RNSVGGroup" as const

export type SVGGroupDescriptor = Descriptor<typeof SVG_GROUP_TYPE_NAME, any>


@Component
export struct SVGGroup {
  @BuilderParam buildCustomComponent: (ctx: ComponentBuilderContext) => void
  ctx: RNOHContext
  tag: number
  @State descriptor: SVGGroupDescriptor = {} as any

  private unregisterDescriptorChangesListener?: () => void = undefined

  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<SVGGroupDescriptor>(this.tag)
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        this.descriptor = (newDescriptor as SVGGroupDescriptor)
      }
    )
  }

  aboutToDisappear() {
    this.unregisterDescriptorChangesListener?.()
  }

  build() {
    Shape() {
      ForEach(this.descriptor.childrenTags, (tag) => {
        RNComponentFactory({ ctx: this.ctx, tag: tag, buildCustomComponent: this.buildCustomComponent })
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