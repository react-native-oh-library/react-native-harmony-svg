//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {commonPathAttributes} from './attributes';

export default register('RNSVGImage', () => {
  return {
    uiViewClassName: 'RNSVGImage',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes,
      ...commonPathAttributes,
      opacity: true,
      x: true,
      y: true,
      width: true,
      height: true,
      src: true,
      align: true,
      meetOrSlice: true,
    },
  };
});
