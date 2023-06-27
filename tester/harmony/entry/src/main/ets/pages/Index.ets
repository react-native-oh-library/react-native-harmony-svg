import { RNApp, ComponentBuilderContext, RNOHContext } from '@ohos/rnoh'
import {
  SVG_VIEW_TYPE_NAME,
  SVGView,
  SVGViewDescriptor,
  SVG_PATH_TYPE_NAME,
  SVGPath,
  SVGPathDescriptor,
  SVG_GROUP_TYPE_NAME,
  SVGGroup,
  SVGGroupDescriptor
} from "@ohos/rnoh-svg"
import { SVGImageView} from "@ohos/svg"


const EXAMPLE = `<?xml version="1.0" encoding="utf-8"?>
<svg version="1.1" id="图层_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
     viewBox="0 0 800 800" xml:space="preserve">
<rect class="brick4" width="800" height="800.5" fill="#6A6ACC"/>
    <g class="brick1" fill="#55346A">
	<path d="M242.4,800.6c-0.2-0.9-0.3-1.9-0.5-2.8c-0.2-0.8-0.3-1.7-0.5-2.5c-0.5-2.5-1.1-5-1.7-7.5l0,0
		c-0.5-1.6-0.8-3.3-1.2-4.8l0,0c-8.1-29.2-22.3-54.7-40.6-73.9c-1.1-1.1-2-2.2-3.1-3.1c-2-2-4.2-4.1-6.4-5.9
		c50.1-46.1,129.1-75.7,218.2-75.7c88.1,0,166.3,29,216.4,74.2c-27.6,23.1-48.1,59.5-55.9,102.1"/>
        <path d="M242.7,802.8"/>
        <path d="M679.6,800.6c-4.4-38.3-24.8-73.4-56.7-102.1c-27.6,23.1-48.1,59.5-55.9,102.1"/>
        <path d="M242.7,802.8"/>
        <path d="M133,800.6h109.2"/>
        <path d="M242.7,802.8c-0.2-0.8-0.3-1.4-0.5-2.2H133c4.4-37.6,24.2-72.3,55.1-100.7c2.2,1.9,4.4,3.9,6.4,5.9
		c1.1,1.1,2,2,3.1,3.1c18.3,19.2,32.5,44.7,40.6,73.9l0,0c0.5,1.6,0.9,3.3,1.2,4.8l0,0c0.6,2.5,1.2,5,1.7,7.5
		c0.2,0.8,0.3,1.7,0.5,2.5c0.2,0.9,0.3,1.9,0.6,2.8C242.5,801.4,242.7,802,242.7,802.8z"/>
</g>
    <path fill="#F0E9ED" d="M398.2,588.6h19.7c17.8,0,32.3,14.4,32.3,32.3l0,0V704c0,23.3-18.9,42.2-42.2,42.2l0,0
	c-23.3,0-42.2-18.9-42.2-42.2v-83.1C365.9,603.1,380.2,588.6,398.2,588.6L398.2,588.6z"/>
    <path fill="#F3BEBB" d="M398.2,555.5h19.7c17.8,0,32.3,14.4,32.3,32.3l0,0v83.1c0,23.3-18.9,42.2-42.2,42.2l0,0
	c-23.3,0-42.2-18.9-42.2-42.2v-83.1C365.9,570,380.2,555.5,398.2,555.5L398.2,555.5z"/>
    <path fill="#D9A7A6" d="M381.7,477.2h52.9c8.6,0,15.6,7,15.6,15.6v118.7c0,12.8-10.3,23.1-23.1,23.1l0,0h-37.9
	c-12.8,0-23.1-10.3-23.1-23.1l0,0V492.8C366,484.2,373.1,477.2,381.7,477.2L381.7,477.2z"/>
    <path class="st6" d="M232.8,318.1h344.6l0,0v121.8c0,95.1-77.1,172.2-172.2,172.4l0,0l0,0c-95.1,0-172.2-77.1-172.4-172.2l0,0V318.1
	L232.8,318.1z"/>
    <path fill="#F3BEBB" d="M567.9,378.3h46.4c12.5,0,22.6,10.2,22.6,22.6l0,0v14.5c0,32.5-26.4,58.9-58.9,58.9l0,0h-10.3
	c-1.9,0-3.3-1.4-3.3-3.3v-89.5C564.7,379.7,566.2,378.3,567.9,378.3L567.9,378.3z"/>
    <path fill="#F3BEBB" d="M238.8,474.3h-10.3c-32.5,0-58.9-26.4-58.9-58.9l0,0v-14.5c0-12.5,10.2-22.6,22.6-22.6l0,0h46.4
	c1.9,0,3.3,1.4,3.3,3.3V471C242.2,472.9,240.6,474.3,238.8,474.3L238.8,474.3z"/>
    <path fill="#F8D7D7" d="M232.8,282.6h344.6l0,0v162.6c0,72.6-58.9,131.5-131.5,131.5l0,0h-81.5c-72.6,0-131.5-58.9-131.5-131.5l0,0
	V282.6H232.8z"/>
    <path fill="#F3BEBB" d="M411.3,578.3h-12c-91.8,0-166.3-74.5-166.3-166.3v35.4c0,91.8,74.5,166.3,166.3,166.3h12
	c91.8,0,166.3-74.5,166.3-166.3v-35.4C577.5,503.8,503.1,578.3,411.3,578.3z"/>
    <path class="brick2" fill="#2B0E27" d="M666.3,190c-1.6-42.2-37-75.3-79.3-73.7c-27.3,0.9-52,16.6-64.8,40.8c-5.2,10-17.3,13.9-27.3,8.9
	c-25-12.6-52.6-19.4-80.6-19.2h-20.8c-27.2,0-54,6.2-78.4,18.3c-9.8,4.8-21.7,0.9-26.9-8.7c-20.5-37-67-50.6-104-30.3
	s-50.6,66.8-30.3,103.8c13.4,24.5,39.2,39.8,67.1,39.8l0,0c1.4,0,2.3,1.1,2.5,2.3c0,0.3,0,0.5-0.2,0.8c-5.2,16.9-7.8,34.4-7.8,52
	v46.8c0,22.2,18.1,40.3,40.3,40.3l0,0h57.9c10.8,0,19.4-8.7,19.4-19.4l0,0V342c-0.2-7.5,5.6-13.9,13.1-14.5c7.8-0.6,14.5,5.3,15,13
	c0,0.3,0,0.6,0,1.1v51.1c0,10.8,8.7,19.4,19.4,19.4l0,0h171c22.2,0,40.3-18.1,40.3-40.3v-46.8c0-17.6-2.7-35.3-7.8-52.2
	c-0.5-1.2,0.3-2.7,1.6-3c0.3-0.2,0.6-0.2,0.8-0.2c0.9,0,2,0,3,0c42.3,0,76.5-34.2,76.5-76.5C666.5,192.1,666.3,191,666.3,190z"/>
    <path fill="#FFFFFF" d="M367.8,489.1H444c10.3,0,18.7,8.4,18.7,18.7l0,0c0,24.2-19.5,43.7-43.7,43.7h-26.2c-24.2,0-43.7-19.5-43.7-43.7
	l0,0C349,497.5,357.4,489.1,367.8,489.1L367.8,489.1z"/>
    <path class="brick3" fill="#222D3C" stroke="#222D3C" stroke-width="14" stroke-linecap="round" stroke-linejoin="round" d="M292.8,456.4c0-12.5,15.1-22.6,34-22.6c18.9,0,34,10.2,34,22.6"/>
    <path class="brick3" fill="#222D3C" stroke="#222D3C" stroke-width="14" stroke-linecap="round" stroke-linejoin="round" d="M444.9,456.4c0-12.5,15.1-22.6,34-22.6s34,10.2,34,22.6"/>
    <ellipse rx="22.2" ry="22.2" fill="none" stroke="#FFD56E" stroke-width="8"  transform="translate(594.7 492.3)"  />
    <ellipse rx="22.2" ry="22.2" fill="none" stroke="#FFD56E" stroke-width="8"  transform="translate(215.2 492.3)"  />
    <path fill="#F3BEBB" d="M395.4,459.9h15.1c4.8,0,8.9,3.9,8.9,8.9l0,0c0,4.8-3.9,8.9-8.9,8.9h-15.1c-4.8,0-8.9-3.9-8.9-8.9l0,0
	C386.5,463.8,390.4,459.9,395.4,459.9z"/>
</svg>`

let storage = LocalStorage.GetShared()

@Entry(storage)
@Component
struct Index {
  @LocalStorageProp('RNOHContext') rnohContext: RNOHContext | undefined = undefined
  model: SVGImageView.SVGImageViewModel = new SVGImageView.SVGImageViewModel()

  aboutToAppear() {
    this.model.setFromString(EXAMPLE)
  }

  @Builder
  buildCustomComponent(ctx: ComponentBuilderContext) {
    if (ctx.descriptor.type === SVG_VIEW_TYPE_NAME) {
      SVGView({
        ctx: ctx.rnohContext,
        descriptor: ctx.descriptor as SVGViewDescriptor,
        buildCustomComponent: this.buildCustomComponent.bind(this)
      })
    } else if (ctx.descriptor.type === SVG_PATH_TYPE_NAME) {
      SVGPath({ ctx: ctx.rnohContext, descriptor: ctx.descriptor as SVGPathDescriptor })
    } else if (ctx.descriptor.type === SVG_GROUP_TYPE_NAME) {
      SVGGroup({
        ctx: ctx.rnohContext,
        descriptor: ctx.descriptor as SVGGroupDescriptor,
        buildCustomComponent: this.buildCustomComponent.bind(this)
      })
    }
  }

  build() {
    Column() {
      SVGImageView({model: this.model}).width(100).height(100).backgroundColor("#EEE")
      // RNApp({
      //   rnohContext: this.rnohContext !,
      //   appName: "app_name",
      //   buildCustomComponent: this.buildCustomComponent.bind(this)
      // })
    }
    .height('100%')
    .width('100%')
  }
}
