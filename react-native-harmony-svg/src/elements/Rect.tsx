import React from 'react';
import {stringifyPropsForFabric, withoutXY} from '../lib/extract/extractProps';
import type {
  CommonPathProps,
  NumberProp,
} from 'react-native-svg/src/lib/extract/types'; // patch: import
import Shape from './Shape';
import RNSVGRect from '../fabric/RectNativeComponent';
import type {NativeMethods} from 'react-native';

export interface RectProps extends CommonPathProps {
  x?: NumberProp;
  y?: NumberProp;
  width?: NumberProp;
  height?: NumberProp;
  rx?: NumberProp;
  ry?: NumberProp;
  opacity?: NumberProp;
}

export default class Rect extends Shape<RectProps> {
  static displayName = 'Rect';

  static defaultProps = {
    x: 0,
    y: 0,
    width: 0,
    height: 0,
  };

  render() {
    const {props} = this;
    const {x, y, width, height, rx, ry} = props;
    const rectProps = stringifyPropsForFabric({x, y, width, height, rx, ry});
    return (
      <RNSVGRect
        ref={(ref: any) => this.refMethod(ref as (Rect & NativeMethods) | null)} // patch: ref type
        {...withoutXY(this, props)}
        {...rectProps}
      />
    );
  }
}
