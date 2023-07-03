//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {commonPathAttributes} from './attributes';

export default register('RNSVGLinearGradient', () => {
  return {
    uiViewClassName: 'RNSVGLinearGradient',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes,
      ...commonPathAttributes,
      opacity: true,
      x1: true,
      y1: true,
      x2: true,
      y2: true,
      gradient: true,
      gradientUnits: true,
      gradientTransform: true,
    },
  };
});
