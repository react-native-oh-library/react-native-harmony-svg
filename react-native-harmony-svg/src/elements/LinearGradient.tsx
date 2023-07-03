import React from 'react';
import extractGradient from 'react-native-svg/src/lib/extract/extractGradient';
import Shape from './Shape';
import RNSVGLinearGradient from '../fabric/LinearGradientNativeComponent';
import {stringifyPropsForFabric} from '../lib/extract/extractProps';
import type {NativeMethods} from 'react-native';
import {LinearGradientProps} from 'react-native-svg/src/elements/LinearGradient';

export default class LinearGradient extends Shape<LinearGradientProps> {
  static displayName = 'LinearGradient';

  static defaultProps = {
    x1: '0%',
    y1: '0%',
    x2: '100%',
    y2: '0%',
  };

  render() {
    const {props} = this;
    const {x1, y1, x2, y2} = props;
    const linearGradientProps = stringifyPropsForFabric({x1, y1, x2, y2});
    return (
      <RNSVGLinearGradient
        ref={(ref: any) =>
          this.refMethod(ref as (LinearGradient & NativeMethods) | null)
        }
        {...linearGradientProps}
        {...extractGradient(props, this)}
      />
    );
  }
}
