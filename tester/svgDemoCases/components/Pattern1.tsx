import React from 'react';
import { ScrollView, Text, View } from 'react-native';
import Svg, {
  Path,
  Mask,
  Rect,
  Image,
  Circle,
  Polygon,
  LinearGradient,
  Stop,
  Defs,
  RNSVGSvgIOS,
  G,
  Line,
  Pattern,
  Symbol
} from 'react-native-svg';

const SVGPatternDemo = () => {
  return (
    <Svg width="100%" height="100%" viewBox="0 0 800 400">
        <Defs>
            <Pattern
                id="TrianglePattern"
                patternUnits="userSpaceOnUse"
                x="0"
                y="0"
                width="50"
                height="50"
                viewBox="0 0 10 10">
                <Rect
                    x="5"
                    y="5"
                    width="5"
                    height="5"
                    stroke="red"
                    strokeWidth="2"
                    fill="yellow"
                />
            </Pattern>
        </Defs>

        <Rect
            x="50"
            y="100"
            width="500"
            height="500"
            stroke="green"
            fill="url(#TrianglePattern)"
        />
        <Symbol id="symbol" viewBox="0 0 150 110" width="100" height="50">
            <Circle cx="50" cy="50" r="40" strokeWidth="8" stroke="red" fill="red" />
            <Circle
            cx="90"
            cy="60"
            r="40"
            strokeWidth="8"
            stroke="green"
            fill="white"
            />
        </Symbol>
    </Svg>
  );
};

export default SVGPatternDemo;
