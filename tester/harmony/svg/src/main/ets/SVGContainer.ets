import { SVGImageView } from "@ohos/svg"
import { RNOHContext, Descriptor, RNViewBase, convertColorValueToRGBA } from "@ohos/rnoh"
import { XMLElementBuilder } from "./XMLElementBuilder"


export type SVGContainerDescriptor = Descriptor<"RNSVGSvgView", {
  backgroundColor?: number
  minX: number,
  minY: number,
  vbWidth: number,
  vbHeight: number
}>

@Component
export struct SVGContainer {
  model: SVGImageView.SVGImageViewModel = new SVGImageView.SVGImageViewModel()
  ctx: RNOHContext
  tag: number
  @State svgString: string = ""

  aboutToAppear() {
    this.setSVGString(this.tag)
    this.ctx.descriptorRegistry.subscribeToDescriptorSubtreeChanges(this.tag, () => {
      this.setSVGString(this.tag)
    })
  }

  private setSVGString(tag: number) {
    let result = `<?xml version="1.0" encoding="utf-8"?>`
    result += this.mapSVGDescriptorToString(tag)
    this.ctx.logger.info("RNOH" + result)
    this.svgString = result
    this.model.setFromString(result)
  }

  private mapSVGDescriptorToString(tag: number): string {
    const descriptor = this.ctx.descriptorRegistry.getDescriptor(tag)
    const viewWidth = descriptor
      .layoutMetrics
      .frame
      .size
      .width
    const viewHeight = descriptor
      .layoutMetrics
      .frame
      .size
      .height
    const builder = new XMLElementBuilder()
    const colorStructParser = (colorStruct) => convertColorValueToRGBA(colorStruct.payload)
    builder.addCustomParser("fill", colorStructParser)
    builder.addCustomParser("stroke", colorStructParser)
    if (descriptor.type === "RNSVGSvgView") {
      builder.setTag("svg")
        .addAttribute("viewBox", `0 0 ${viewWidth} ${viewHeight}`)
        .addAttribute("xml:space", "preserve")
        .addAttributes(descriptor.props)
        .addChildren(this.mapChildrenTagsToSVGString(descriptor.childrenTags))
    } else if (descriptor.type === "RNSVGGroup") {
      builder.setTag("g")
        .addChildren(this.mapChildrenTagsToSVGString(descriptor.childrenTags))
        .addAttributes(descriptor.props)
    } else if (descriptor.type === "RNSVGPath") {
      builder.setTag("path")
        .addAttributes(descriptor.props)
    } else {
      this.ctx.logger.error(`Unknown SVG descriptor: ${JSON.stringify(descriptor)}`)
    }
    return builder?.build() ?? ""
  }

  private mapChildrenTagsToSVGString(childrenTags: number[]): string {
    return childrenTags.reduce((acc, childrenTag) => {
      acc += this.mapSVGDescriptorToString(childrenTag)
      return acc
    }, "")
  }

  build() {
    RNViewBase({ ctx: this.ctx, tag: this.tag }) {
      SVGImageView({ model: this.model }).width("100%").height("100%")
    }
  }
}
