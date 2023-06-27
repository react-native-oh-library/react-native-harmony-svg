import { SVGImageView } from "@ohos/svg"


const EXAMPLE = `<?xml version="1.0" encoding="utf-8"?>
<svg version="1.1" id="图层_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
     viewBox="0 0 800 800" xml:space="preserve">
  <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />
</svg>`


@Component
export struct SVGContainer {
  model: SVGImageView.SVGImageViewModel = new SVGImageView.SVGImageViewModel()

  aboutToAppear() {
    this.model.setFromString(EXAMPLE)
  }

  build() {
    Stack() {
      SVGImageView({ model: this.model }).width(100).height(100).backgroundColor("#EEE")
    }
  }
}
