//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';

export default register('RNSVGGroup', () => {
  return {
    uiViewClassName: 'RNSVGGroup',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes.UIView,
      fill: true,
      stroke: true,
      strokeWidth: true,
    },
  };
});
