//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {groupAttributes} from './GroupNativeComponent';

export default register('RNSVGSvgView', () => {
  return {
    uiViewClassName: 'RNSVGSvgView',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes.UIView,
      ...groupAttributes,
      minX: true,
      minY: true,
      vbWidth: true,
      vbHeight: true,
      align: true,
      meetOrSlice: true,
    },
  };
});
