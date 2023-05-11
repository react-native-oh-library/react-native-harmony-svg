//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';

export default register('RNSVGPath', () => {
  return {
    uiViewClassName: 'RNSVGPath',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes.UIView,
      d: true,
    },
  };
});
