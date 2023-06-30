//@ts-ignore
import {register} from 'react-native/Libraries/Renderer/shims/ReactNativeViewConfigRegistry';
//@ts-ignore
import ReactNativeViewAttributes from 'react-native/Libraries/Components/View/ReactNativeViewAttributes';
import {commonPathAttributes, fontAttributes} from './attributes';

export default register('RNSVGClipPath', () => {
  return {
    uiViewClassName: 'RNSVGClipPath',
    bubblingEventTypes: {},
    directEventTypes: {},
    validAttributes: {
      ...ReactNativeViewAttributes.UIView,
      ...commonPathAttributes,
      ...fontAttributes,
      id: true,
    },
  };
});
