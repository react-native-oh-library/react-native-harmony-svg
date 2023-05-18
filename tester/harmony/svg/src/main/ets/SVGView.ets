import {
  Descriptor,
  ComponentBuilderContext,
  RNComponentFactory,
  RNOHContext,
  convertColorValueToRGBA
} from '@ohos/rnoh'

export const SVG_VIEW_TYPE_NAME = "RNSVGSvgView" as const

export type SVGViewDescriptor = Descriptor<typeof SVG_VIEW_TYPE_NAME, {
  backgroundColor?: number
  minX: number,
  minY: number,
  vbWidth: number,
  vbHeight: number
}>


@Component
export struct SVGView {
  @Prop descriptor: SVGViewDescriptor
  @BuilderParam buildCustomComponent: (ctx: ComponentBuilderContext) => void
  @Consume("RNOHContext") ctx: RNOHContext

  aboutToAppear() {
    console.log("RNOH::SVGView", JSON.stringify(this.descriptor))
  }

  scaleValue() {
    return Math.max(this.scaleX(), this.scaleY())
  }

  scaleX() {
    if (!this.descriptor.props.vbWidth) {
      return 1
    }
    return this.descriptor
      .layoutMetrics
      .frame
      .size
      .width / this.descriptor.props.vbWidth
  }

  scaleY() {
    if (!this.descriptor.props.vbHeight) {
      return 1
    }
    return this.descriptor
      .layoutMetrics
      .frame
      .size
      .height / this.descriptor.props.vbHeight
  }

  build() {
    Stack() {
      Shape() {
        ForEach(this.descriptor.childrenTags, (tag) => {
          RNComponentFactory({ tag: tag, buildCustomComponent: this.buildCustomComponent })
        }, tag => tag)
      }
      .width("100%")
      .height("100%")
      .scale({ x: this.scaleValue(), y: this.scaleValue(), centerX: 0, centerY: 0 })
      .offset({ x: -(this.descriptor.props.minX ?? 0), y: -(this.descriptor.props.minY ?? 0) })
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
    .clip(true)
  }
}
