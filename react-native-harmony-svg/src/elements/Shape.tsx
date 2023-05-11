import {Component} from 'react';
import type {NativeMethods} from 'react-native';

export default class Shape<P> extends Component<P> {
  root: (Shape<P> & NativeMethods) | null = null;
  constructor(props: Readonly<P> | P) {
    super(props);
  }
  refMethod: (instance: (Shape<P> & NativeMethods) | null) => void = (
    instance: (Shape<P> & NativeMethods) | null,
  ) => {
    this.root = instance;
  };
}
