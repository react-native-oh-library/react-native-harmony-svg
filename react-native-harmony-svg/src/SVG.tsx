import React from 'react'
//@ts-ignore
import { register } from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry'
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes'

const SVGNativeComponent = register('SVG', () => {
  return {
    uiViewClassName: 'SVG',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes.UIView,
    },
  }
})

export class SVG extends React.Component<any> {
  render() {
    return <SVGNativeComponent {...this.props} />
  }
}
