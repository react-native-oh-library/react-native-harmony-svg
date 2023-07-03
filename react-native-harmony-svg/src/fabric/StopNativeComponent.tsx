//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {commonPathAttributes} from './attributes';

export default register('RNSVGStop', () => {
  return {
    uiViewClassName: 'RNSVGStop',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes,
      ...commonPathAttributes,
      stopColor: true,
      stopOpacity: true,
      offset: true,
    },
  };
});
