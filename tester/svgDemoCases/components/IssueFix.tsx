import React, {Component} from 'react';
import Svg, {
  Circle,
  Ellipse,
  G,
  Text,
  TSpan,
  TextPath,
  Path,
  Polygon,
  Polyline,
  Line,
  Rect,
  Use,
  Image,
  Symbol,
  Defs,
  LinearGradient,
  Stop,
} from 'react-native-svg';
import {View, StyleSheet, ScrollView} from 'react-native';
import {Tester, Filter, TestCase, TestSuite} from '@rnoh/testerino';

class SvgLayoutExample extends Component {
  static title = 'SVG with flex layout';
  render() {
    return (
      <View style={styles.container}>
        <Svg style={styles.svg}>
          <Rect
            width="80%"
            height="80%"
            x="10%"
            y="10%"
            fill="purple"
            stroke="yellow"
            strokeWidth="4"
          />
          <Line
            x1="10%"
            y1="10%"
            x2="90%"
            y2="90%"
            stroke="yellow"
            strokeWidth="4"
          />
          <Line
            x1="10%"
            y1="90%"
            x2="90%"
            y2="10%"
            stroke="yellow"
            strokeWidth="4"
          />
        </Svg>
      </View>
    );
  }
}

const samples = [SvgLayoutExample];

const styles = StyleSheet.create({
  container: {
    flex: 1,
    height: 100,
    width: 200,
    backgroundColor: 'red',
  },
  svg: {
    height: '80%',
    width: '80%',
    flex: 1,
    alignSelf: 'stretch',
  },
});

export default function () {
  return (
    <Tester style={{flex: 1}}>
      <ScrollView>
        <TestCase itShould="SVG with flex layout">
          <SvgLayoutExample />
        </TestCase>
      </ScrollView>
    </Tester>
  );
}
