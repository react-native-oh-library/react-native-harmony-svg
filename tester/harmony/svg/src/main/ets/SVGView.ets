import { Descriptor, ComponentBuilderContext, RNComponentFactory } from '@ohos/rnoh'

export const SVG_VIEW_TYPE_NAME = "RNSVGSvgView" as const

export type SVGViewDescriptor = Descriptor<typeof SVG_VIEW_TYPE_NAME, any>


@Component
export struct SVGView {
  @Prop descriptor: SVGViewDescriptor
  @BuilderParam buildChildren: (childrenTags: number[]) => void

  build() {
    Shape() {
      this.buildChildren(this.descriptor.childrenTags)
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
    .backgroundColor("yellow")
    .borderWidth(1)
  }
}
