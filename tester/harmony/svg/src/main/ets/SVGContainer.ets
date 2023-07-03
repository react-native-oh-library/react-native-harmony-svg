import { SVGImageView } from "@ohos/svg"
import { RNOHContext, Descriptor, RNViewBase, convertColorValueToRGBA } from "@ohos/rnoh"
import { XMLElementBuilder } from "./XMLElementBuilder"
import display from '@ohos.display';

export type SVGContainerDescriptor = Descriptor<"RNSVGSvgView", {
  backgroundColor?: number
  minX: number,
  minY: number,
  vbWidth: number,
  vbHeight: number
}>

const SVG_TAG_BY_DESCRIPTOR_TYPE = {
  RNSVGSvgView: "svg",
  RNSVGGroup: "g",
  RNSVGPath: "path",
  RNSVGRect: "rect",
  RNSVGCircle: "circle",
  RNSVGDefs: "defs",
  RNSVGClipPath: "clipPath",
  RNSVGImage: "image",
  RNSVGLinearGradient: "linearGradient",
  RNSVGStop: "stop",
}

type ViewBox = {
  width: number,
  height: number
  scale: number
}

@Component
export struct SVGContainer {
  static DESCRIPTOR_TYPE = "RNSVGSvgView"
  model: SVGImageView.SVGImageViewModel = new SVGImageView.SVGImageViewModel()
  ctx: RNOHContext
  tag: number
  @State private debugModeEnabled: boolean = false
  @State private svgString: string = ""

  aboutToAppear() {
    setTimeout(() => {
      this.model.isScale = false
      const scale = this.extractViewBox(this.tag).scale
      this.model.context.scale(scale, scale)
      this.setSVGString(this.tag)
    }, 0) // Scaling is not set if this method is run immediately
    this.ctx.descriptorRegistry.subscribeToDescriptorSubtreeChanges(this.tag, () => {
      this.setSVGString(this.tag)
    })
  }

  private setSVGString(tag: number) {
    let result = `<?xml version="1.0" encoding="utf-8"?>`
    result += this.mapSVGDescriptorToString(tag)
    this.svgString = result
    this.render(result)
  }

  private render(str: string) {
    this.model.canvas.clear()
    this.model.setFromString(str)
  }

  private extractViewBox(tag: number): ViewBox {
    const descriptor = this.ctx.descriptorRegistry.getDescriptor(tag)
    const p = descriptor.props
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
    const width = p["vbWidth"] ?? viewWidth
    const height = p["vbHeight"] ?? viewHeight

    return {
      width,
      height,
      scale: Math.min(viewWidth / width, viewHeight / height) * display.getDefaultDisplaySync().densityPixels
    }
  }

  private mapSVGDescriptorToString(tag: number): string {
    const descriptor = this.ctx.descriptorRegistry.getDescriptor(tag)
    const builder = new XMLElementBuilder()
    const colorStructParser = (colorStruct) => convertColorValueToRGBA(colorStruct.payload)
    builder.addCustomParser("fill", colorStructParser)
    builder.addCustomParser("stroke", colorStructParser)

    if (descriptor.type === "RNSVGSvgView") {
      const viewBox = this.extractViewBox(tag)
      const p = descriptor.props
      builder.setTag("svg")
        .addAttribute("viewBox", `${p["minX"] ?? 0} ${p["minY"] ?? 0} ${viewBox.width} ${viewBox.height}`)
        .addAttribute("preserveAspectRatio", p["align"] && p["meetOrSlice"] !== undefined ? p["align"] + ' ' + ["meet", "slice", "none"][p["meetOrSlice"]] : undefined)
    } else if (descriptor.type in SVG_TAG_BY_DESCRIPTOR_TYPE) {
      builder.setTag(SVG_TAG_BY_DESCRIPTOR_TYPE[descriptor.type])
        .addAttributes(descriptor.props, true)
    } else {
      this.ctx.logger.error(`Unknown SVG descriptor: ${JSON.stringify(descriptor)}`)
      return "";
    }
    builder
      .addChildren(this.mapChildrenTagsToSVGString(descriptor.childrenTags))
    return builder.build()
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
      if (this.debugModeEnabled) Text(this.svgString).fontSize(10).opacity(0.25).fontColor("rgba(0,128,0,1)")
    }
  }
}
