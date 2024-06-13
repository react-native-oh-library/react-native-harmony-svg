import * as React from 'react';
import type { ImageProps as RNImageProps, NativeMethods, ImageResolvedAssetSource } from 'react-native';
import { Image } from 'react-native';
import { alignEnum, meetOrSliceTypes } from 'react-native-svg/src/lib/extract/extractViewBox';
import {
  stringifyPropsForFabric,
  withoutXY,
} from 'react-native-svg/src/lib/extract/extractProps';
import type { CommonPathProps, NumberProp } from 'react-native-svg/src/lib/extract/types';
import Shape from './Shape';
import RNSVGImage from 'react-native-svg/src/fabric/ImageNativeComponent';
import RNSVGImageModule from '../fabric/NativeSvgImageModule';

const spacesRegExp = /\s+/;

export interface ImageProps extends CommonPathProps {
  x?: NumberProp;
  y?: NumberProp;
  width?: NumberProp;
  height?: NumberProp;
  xlinkHref?: RNImageProps['source'] | string;
  href?: RNImageProps['source'] | string;
  preserveAspectRatio?: string;
  opacity?: NumberProp;
}

export default class SvgImage extends Shape<ImageProps> {
  static displayName = 'Image';

  static defaultProps = {
    x: 0,
    y: 0,
    width: 0,
    height: 0,
    preserveAspectRatio: 'xMidYMid meet',
  };

  constructor(props: ImageProps) {
    super(props);
    this.state = {
      href: props.href || props.xlinkHref,
    };
    if (this.state.href && typeof this.state.href === 'string' && this.state.href.startsWith('http')) {
      this.fetchBase64String(this.state.href);
    }
  }

  fetchBase64String = (href: string) => {
    const src = !href
      ? null
      : Image.resolveAssetSource(
        typeof href === 'string' ? { uri: href } : href
      )
    if (src) {
      RNSVGImageModule.getBase64String(src.uri).then((res) => {
        this.setState({ href: res });
      }
      ).catch((error) => {
        console.error(`getBase64String error: ${error.message}`);
      });
    }

  };

  componentDidUpdate(prevProps: ImageProps) {
    if (prevProps.href !== this.props.href) {
      const href = this.props.href || this.props.xlinkHref;
      if (href && typeof href === 'string' && href.startsWith('http')) {
        this.fetchBase64String(href);
      } else {
        this.setState({ href: href })
      }
    }
  }

  render() {
    const { props } = this;
    const {
      preserveAspectRatio,
      x,
      y,
      width,
      height,
      xlinkHref,
      href = xlinkHref,
    } = props;
    const modes = preserveAspectRatio
      ? preserveAspectRatio.trim().split(spacesRegExp)
      : [];
    const align = modes[0];
    const meetOrSlice: 'meet' | 'slice' | 'none' | string | undefined =
      modes[1];
    const stringifiedImageProps = stringifyPropsForFabric({
      x,
      y,
      width,
      height,
    });
    const imageProps = {
      ...stringifiedImageProps,
      meetOrSlice: meetOrSliceTypes[meetOrSlice] || 0,
      align: alignEnum[align] || 'xMidYMid',
      src: !this.state.href
        ? null
        : Image.resolveAssetSource(
          typeof this.state.href === 'string' ? { uri: this.state.href } : this.state.href
        ),
    };

    return (
      <RNSVGImage
        ref={(ref) => this.refMethod(ref as (SvgImage & NativeMethods) | null)}
        {...withoutXY(this, props)}
        {...imageProps}
      />
    );
  }
}
