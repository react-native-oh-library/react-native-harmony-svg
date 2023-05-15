import { Descriptor } from '@ohos/rnoh'
import type { DescriptorRegistry } from '@ohos/rnoh/src/main/ets/DescriptorRegistry'

export const SVG_TYPE_NAME = "RNSVGSvgView" as const

export type SVGProps = any;

export type SVGDescriptor = Descriptor<typeof SVG_TYPE_NAME, SVGProps>

@Component
export struct SVG {
  @Prop descriptor: SVGDescriptor
  @Consume('__RN_DESCRIPTOR_REGISTRY') descriptorRegistry: DescriptorRegistry
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private offContext: OffscreenCanvasRenderingContext2D = new OffscreenCanvasRenderingContext2D(this.descriptor.layoutMetrics.frame.size.width, this.descriptor.layoutMetrics.frame.size.height, this.settings)

  paint(tag: number) {
    this.paintFromTag(tag)
    var image = this.offContext.transferToImageBitmap()
    this.context.transferFromImageBitmap(image)
    console.log("RNOH::SVG paint")
  }

  paintFromTag(tag: number) {
    const descriptor = this.descriptorRegistry.getDescriptor(tag)
    if (descriptor.type === "RNSVGSvgView") {
      this.paintSvgView(descriptor as SVGDescriptor)
    }
    for (const tag of descriptor.childrenTags) {
      this.paintFromTag(tag)
    }
  }

  paintSvgView(descriptor: SVGDescriptor) {
    this.offContext.lineWidth = 10
    this.offContext.strokeStyle = '#0000ff'
    this.offContext.strokeRect(25, 25, 155, 105)
  }

  build() {
    Canvas(this.context)
      .onReady(() => {
        this.paint(this.descriptor.tag)
      })
      .width(this.descriptor.layoutMetrics.frame.size.width)
      .height(this.descriptor.layoutMetrics.frame.size.height)
      .position(this.descriptor.layoutMetrics.frame.origin)
      .backgroundColor("yellow")
      .borderWidth(1)
  }
}
