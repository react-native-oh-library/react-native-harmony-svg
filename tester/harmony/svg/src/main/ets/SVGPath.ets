import { Descriptor } from '@ohos/rnoh'
import type { DescriptorRegistry } from '@ohos/rnoh/src/main/ets/DescriptorRegistry'

export const SVG_PATH_TYPE_NAME = "RNSVGPath" as const

export type SVGPathDescriptor = Descriptor<typeof SVG_PATH_TYPE_NAME, { d: string }>


@Component
export struct SVGPath {
  @Prop descriptor: SVGPathDescriptor

  aboutToAppear() {
    console.log("RNOH::SVGPath", JSON.stringify(this.descriptor))
  }

  build() {
    Path()
      .width("100%")
      .height("100%")
      .commands(this.descriptor.props.d)
      .stroke("red")
      .strokeWidth(8)
      .position(this.descriptor.layoutMetrics.frame.origin)
  }
}
