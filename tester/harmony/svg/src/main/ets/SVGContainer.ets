import { SVGImageView } from "@ohos/svg"
import { SVG } from "@ohos/svg/src/main/ets/components/SVG"
import { SVGBase } from "@ohos/svg/src/main/ets/components/utils/SVGBase"
import { RNOHContext, Descriptor, RNViewBase } from "@ohos/rnoh"


const EXAMPLE = `<?xml version="1.0" encoding="utf-8"?>
<svg version="1.1" id="图层_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
     viewBox="0 0 800 800" xml:space="preserve">
  <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />
</svg>`


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
    // this.model.setFromString(EXAMPLE)
  }

  private setSVGString(tag: number) {
    let result = `<?xml version="1.0" encoding="utf-8"?>`
    result += this.mapSVGDescriptorToString(tag)
    this.svgString = result
    this.model.setFromString(result)
  }

  private mapSVGDescriptorToString(tag: number): string {
    const descriptor = this.ctx.descriptorRegistry.getDescriptor(tag)
    let result = ""
    if (descriptor.type === "RNSVGSvgView") {
      result += `<svg version="1.1" id="图层_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
     viewBox="0 0 800 800" xml:space="preserve">${this.mapChildrenTagsToSVGString(descriptor.childrenTags)}</svg>`
    } else if (descriptor.type === "RNSVGGroup") {
      result += `<g>${this.mapChildrenTagsToSVGString(descriptor.childrenTags)}</g>`
    } else if (descriptor.type === "RNSVGPath") {
      result += `<path d="${descriptor.props["d"]}" />`
    } else {
      this.ctx.logger.error(`Unknown SVG descriptor: ${JSON.stringify(descriptor)}`)
    }
    return result
  }

  private mapChildrenTagsToSVGString(childrenTags: number[]): string {
    return childrenTags.reduce((acc, childrenTag) => {
      acc += this.mapSVGDescriptorToString(childrenTag)
      return acc
    }, "")
  }

  build() {
    RNViewBase({ctx: this.ctx, tag: this.tag}) {
      SVGImageView({ model: this.model }).width("100%").height("100%")
    }
  }
}
