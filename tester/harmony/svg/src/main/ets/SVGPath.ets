import { Descriptor, RNOHContext, convertColorValueToRGBA } from '@ohos/rnoh'

export const SVG_PATH_TYPE_NAME = "RNSVGPath" as const

type ColorStruct = {
  type: 0,
  payload: number
}

export type SVGPathDescriptor = Descriptor<typeof SVG_PATH_TYPE_NAME, {
  d: string,
  fill?: ColorStruct
  stroke?: ColorStruct
  strokeWidth?: string
}>


@Component
export struct SVGPath {
  ctx: RNOHContext
  tag: number
  @State descriptor: SVGPathDescriptor = {} as any
  private unregisterDescriptorChangesListener?: () => void = undefined

  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<SVGPathDescriptor>(this.tag)
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        this.descriptor = (newDescriptor as SVGPathDescriptor)
      }
    )
  }

  aboutToDisappear() {
    this.unregisterDescriptorChangesListener?.()
  }

  build() {
    Path()
      .width("100%")
      .height("100%")
      .antiAlias(true)
      .commands(this.descriptor.props.d)
      .position(this.descriptor.layoutMetrics.frame.origin)
      .strokeWidth(parseFloat(this.descriptor.props.strokeWidth ?? "0"))
      .stroke(this.descriptor.props.stroke?.payload ? convertColorValueToRGBA(this.descriptor.props.stroke?.payload) : undefined)
      .fill(this.descriptor.props.fill?.payload ? convertColorValueToRGBA(this.descriptor.props.fill?.payload) : undefined)
  }
}
