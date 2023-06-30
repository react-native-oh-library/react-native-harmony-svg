//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {commonPathAttributes} from './attributes';

export default register('RNSVGRect', () => {
  return {
    uiViewClassName: 'RNSVGRect',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes.UIView,
      ...commonPathAttributes,
      x: true,
      y: true,
      width: true,
      height: true,
      rx: true,
      ry: true,
      opacity: true,
    },
  };
});
