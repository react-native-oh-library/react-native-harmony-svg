import React, {Component} from 'react';
import {
  Svg,
  Circle,
  Defs,
  Marker,
  Rect,
  Ellipse,
  Line,
  Polygon,
  Path,
} from 'react-native-svg';
import { ScrollView } from 'react-native'
import {Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';

class LineExample extends Component {
  static title = 'Triangle shaped marker on line';
  render() {
    return (
      <Svg height="200" width="200">
        <Defs>
          <Marker
            id="selection"
            markerUnits="userSpaceOnUse"
            refX="0"
            refY="0"
            minX="5"
            minY="5"
            vbWidth="10"
            vbHeight="10"
            aline="none"
            meetOrSlice="0"
            orient="auto">
            <Polygon
              points="0,0 -5,20 10,30"
              fill="lime"
              stroke="purple"
              strokeWidth="1"
            />
          </Marker>
        </Defs>
        <Line
          x1="20"
          y1="10%"
          x2="60%"
          y2="60%"
          stroke="red"
          strokeWidth="2"
          marker="url(#selection)"
        />
      </Svg>
    );
  }
}

class PathExample extends Component {
  static title = 'Path shaped marker on line';
  render() {
    return (
      <Svg height="200" width="400" viewBox="0 0 300 100">
        <Defs>
          <Marker
            id="arrow"
            viewBox="0 0 30 10"
            refX="100"
            refY="5"
            markerWidth="60"
            markerHeight="60"
            orient="auto-start-reverse"
          >
            <Path fill="blue" d="M 0 0 L 10 5 L 0 10 z" />
          </Marker>
        </Defs>
        <Line
          x1="10"
          y1="10"
          x2="90"
          y2="90"
          stroke="black"
          strokeWidth="3"
          markerEnd="url(#arrow)"
        />
      </Svg>
    );
  }
}

const icon = (
  <Svg height="30" width="30" viewBox="0 0 3000 2500">
    <Defs>
      <Marker
        id="Triangle"
        // viewBox="0 0 10 10"
        refX="0"
        refY="5"
        markerUnits="strokeWidth"
        markerWidth="4"
        markerHeight="3"
        orient="auto">
        <Path fill="blue" d="M 0 0 L 10 5 L 0 10 z" />
      </Marker>
    </Defs>
    <Path
      d="M 1000 750 L 2000 750 L 2500 1250"
      fill="none"
      stroke="black"
      strokeWidth="70"
      markerEnd="url(#Triangle)"
      markerStart="url(#Triangle)"
    />
  </Svg>
);

const samples = [
  LineExample,
  PathExample,
];
export {icon, samples};

export default function () {
    return (
        <Tester style={{flex: 1}}>
             <ScrollView>
                <TestCase itShould="Triangle shaped marker on line">
                    <LineExample />
                </TestCase>
                <TestCase itShould="Path shaped marker on line">
                    <PathExample />
                </TestCase>
            </ScrollView>
        </Tester>      
    )
  }
