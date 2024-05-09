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
} from 'react-native-svg';

const SVGDemo = () => {
  return (
    <View>
      <Svg viewBox="0 0 600 500" width={400} height={400} color="green" preserveAspectRatio="xMinYMid slice">
        <Mask id="myMask">
          <Rect opacity="1.0" x="0" y="0" width="100" height="100" fill="white" />
        </Mask>
        <G stroke="pink" fill="pink" strokeWidth={10} opacity="0.5">
          <Rect
            x="50"
            y="50"
            width="180"
            height="170"
            stroke="currentColor"
            fill="yellow"
            strokeDashoffset={10}
            strokeLinecap="round"
            strokeLinejoin="bevel"
            rx="20"
            ry="40"
          />
          <Circle
            cx="50"
            cy="50"
            r="45"
            stroke="blue"
            strokeWidth="2.5"
            fill="green"
            mask="url(#myMask)"
          />
          <Line
            x1="30"
            y1="40"
            x2="200"
            y2="180"
            stroke="grey"
            strokeWidth={10}
            strokeLinecap="round"
            strokeLinejoin="bevel"
          />
          <Line
            x1="30"
            y1="70"
            x2="300"
            y2="70"
            stroke="blue"
            strokeDasharray="20 10"
          />
          <Line
            x1="30"
            y1="110"
            x2="300"
            y2="110"
            stroke="blue"
            strokeDasharray="20 10 30"
          /></G>
      </Svg>
    </View>
  );
};

export default SVGDemo;
