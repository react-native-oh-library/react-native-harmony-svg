import {
  FillProps,
  ClipProps,
  VectorEffectProps,
  DefinitionProps,
  StrokeProps,
  FontProps,
  TransformProps,
  CommonMaskProps,
  CommonMarkerProps,
  CommonPathProps,
  TextSpecificProps,
} from 'react-native-svg';

type AttributesFromProps<TProps> = Required<{
  [K in keyof TProps]: any;
}>;

export const fillAttributes: AttributesFromProps<FillProps> = {
  fill: true,
  fillOpacity: true,
  fillRule: true,
};

export const clipAttributes: AttributesFromProps<ClipProps> = {
  clipPath: true,
  clipRule: true,
};

export const vectorEffectAttributes: AttributesFromProps<VectorEffectProps> = {
  vectorEffect: true,
};

export const definitionAttributes: AttributesFromProps<DefinitionProps> = {
  id: true,
};

export const strokeAttributes: AttributesFromProps<StrokeProps> = {
  stroke: true,
  strokeWidth: true,
  strokeOpacity: true,
  strokeDasharray: true,
  strokeDashoffset: true,
  strokeLinecap: true,
  strokeLinejoin: true,
  strokeMiterlimit: true,
  vectorEffect: true,
};

export const fontAttributes: AttributesFromProps<FontProps> = {
  fontStyle: true,
  fontVariant: true,
  fontWeight: true,
  fontStretch: true,
  fontSize: true,
  fontFamily: true,
  textAnchor: true,
  textDecoration: true,
  letterSpacing: true,
  wordSpacing: true,
  kerning: true,
  fontFeatureSettings: true,
  fontVariantLigatures: true,
  fontVariationSettings: true,
  font: true,
};

export const transformAttributes: AttributesFromProps<TransformProps> = {
  translate: true,
  translateX: true,
  translateY: true,
  origin: true,
  originX: true,
  originY: true,
  scale: true,
  scaleX: true,
  scaleY: true,
  skew: true,
  skewX: true,
  skewY: true,
  rotation: true,
  x: true,
  y: true,
  transform: true,
};

export const commonMaskAttributes: AttributesFromProps<CommonMaskProps> = {
  mask: true,
};

export const commonMarkerAttributes: AttributesFromProps<CommonMarkerProps> = {
  marker: true,
  markerStart: true,
  markerMid: true,
  markerEnd: true,
};

export const commonPathAttributes: Partial<
  AttributesFromProps<CommonPathProps>
> = {
  ...fillAttributes,
  ...strokeAttributes,
  ...clipAttributes,
  ...transformAttributes,
  ...vectorEffectAttributes,
  ...definitionAttributes,
  ...commonMarkerAttributes,
  ...commonMaskAttributes,
};

export const textSpecificAttributes: Partial<
  AttributesFromProps<TextSpecificProps>
> = {
  ...commonPathAttributes,
  alignmentBaseline: true,
  baselineShift: true,
  verticalAlign: true,
  lengthAdjust: true,
  textLength: true,
  fontData: true,
  fontFeatureSettings: true,
};
