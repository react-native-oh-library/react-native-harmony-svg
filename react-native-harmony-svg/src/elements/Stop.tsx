import React from 'react';
import Shape from './Shape';
import RNSVGStop from '../fabric/StopNativeComponent';
import type {NativeMethods} from 'react-native';
import {StopProps} from 'react-native-svg/src/elements/Stop';

export default class Stop extends Shape<StopProps> {
  static displayName = 'Stop';

  render() {
    const {props} = this;

    return (
      <RNSVGStop
        ref={(ref: any) => this.refMethod(ref as (Stop & NativeMethods) | null)}
        {...props}
      />
    );
  }
}
