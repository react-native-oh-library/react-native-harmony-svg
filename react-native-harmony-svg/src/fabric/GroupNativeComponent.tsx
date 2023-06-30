//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {commonPathAttributes, fontAttributes} from './attributes';

export const groupAttributes = {
  ...ReactNativeViewAttributes.UIView,
  ...commonPathAttributes,
  ...fontAttributes,
  opacity: true,
};

export default register('RNSVGGroup', () => {
  return {
    uiViewClassName: 'RNSVGGroup',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: groupAttributes,
  };
});
