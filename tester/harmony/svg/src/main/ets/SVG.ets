import { Descriptor } from '@ohos/rnoh'
export const SVG_TYPE_NAME = "SVG" as const
export type SVGProps = any;
export type SVGDescriptor = Descriptor<typeof SVG_TYPE_NAME, SVGProps>

@Component
export struct SVG {
  @Prop descriptor: SVGDescriptor

  build() {
    Stack() {
    }
    .width(this.descriptor.props.width)
    .height(this.descriptor.props.height)
    .position({ x: this.descriptor.props.left, y: this.descriptor.props.top })
    .backgroundColor("red")
  }
}
