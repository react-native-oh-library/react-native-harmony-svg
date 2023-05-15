import { RNApp, RNInstance, ComponentBuilderContext, RNComponentFactory } from '@ohos/rnoh'
import {
  SVG_VIEW_TYPE_NAME,
  SVGView,
  SVGViewDescriptor,
  SVG_PATH_TYPE_NAME,
  SVGPath,
  SVGPathDescriptor
} from "@ohos/rnoh-svg"


@Entry
@Component
struct Index {
  //  @Builder
  //  buildCustomComponentFromTag(tag: number) {
  //    RNComponentFactory({ tag: tag, buildCustomComponent: this.buildCustomComponent.bind(this) })
  //  }

  @Builder buildChildren(childrenTags: number[]) {
    ForEach(childrenTags, (childrenTag) => {
      RNComponentFactory({ tag: childrenTag, buildCustomComponent: this.buildCustomComponent })
    }, childrenTag => childrenTag)

  }

  @Builder
  buildCustomComponent(ctx: ComponentBuilderContext) {
    if (ctx.descriptor.type === SVG_VIEW_TYPE_NAME) {
      SVGView({ descriptor: ctx.descriptor as SVGViewDescriptor, buildChildren: this.buildChildren })
    } else if (ctx.descriptor.type === SVG_PATH_TYPE_NAME) {
      SVGPath({ descriptor: ctx.descriptor as SVGPathDescriptor })
    }
  }

  build() {
    Column() {
      RNApp({
        rnInstance: new RNInstance((ctx) => []),
        buildCustomComponent: this.buildCustomComponent.bind(this),
      })
    }
    .height('100%')
    .width('100%')
  }
}
