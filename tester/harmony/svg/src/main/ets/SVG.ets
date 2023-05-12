import { Descriptor } from '@ohos/rnoh'
export const SVG_TYPE_NAME = "SVG" as const
export type SVGProps = any;
export type SVGDescriptor = Descriptor<typeof SVG_TYPE_NAME, SVGProps>

@Component
export struct SVG {
  @Prop descriptor: SVGDescriptor

   aboutToAppear() {
     console.log("RNOH::SVG", JSON.stringify(this.descriptor))
   }

  build() {
    Stack() {
    }
    .width(this.descriptor.layoutMetrics.frame.size.width)
    .height(this.descriptor.layoutMetrics.frame.size.height)
    .position(this.descriptor.layoutMetrics.frame.origin)
    .backgroundColor("red")
    .borderWidth(1)
  }
}
