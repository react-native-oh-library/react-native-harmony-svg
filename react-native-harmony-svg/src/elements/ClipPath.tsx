import type {ReactNode} from 'react';
import React from 'react';
import {extract} from 'react-native-svg/src/lib/extract/extractProps';
import Shape from './Shape';
import RNSVGClipPath from '../fabric/ClipPathNativeComponent';

export interface ClipPathProps {
  children?: ReactNode;
  id?: string;
}

export default class ClipPath extends Shape<ClipPathProps> {
  static displayName = 'ClipPath';

  render() {
    const {props} = this;
    return (
      <RNSVGClipPath
        ref={this.refMethod}
        {...extract(this, props)}
        {...{id: props.id}}>
        {props.children}
      </RNSVGClipPath>
    );
  }
}
