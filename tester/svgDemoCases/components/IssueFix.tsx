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

class Issue178 extends Component {
  static title = 'Stroke LinearGradient';
  render() {
    return (
      <Svg style={{height: 200, width: 374.1538391113281}}>
        <Defs key={'gradient'}>
          <LinearGradient id={'gradient'} x1="0%" y1="0%" x2="100%" y2="0%">
            <Stop offset={'0%'} stopColor={'rgb(134, 65, 244)'} />
            <Stop offset={'100%'} stopColor={'rgb(66, 194, 244)'} />
          </LinearGradient>
        </Defs>
        <Path
          d="M0,61.14285714285714L26.725274222237722,97.71428571428572L53.450548444475444,70.28571428571428L80.17582266671316,20L106.90109688895089,110.51428571428572L133.62637111118863,128.79999999999998L160.35164533342632,29.142857142857146L187.07691955566406,23.657142857142865L213.80219377790178,74.85714285714286L240.52746800013952,58.39999999999999L267.25274222237726,155.31428571428572L293.9780164446149,84.91428571428571L320.70329066685264,61.14285714285714L347.4285648890904,125.14285714285715L374.1538391113281,180"
          fillOpacity={0}
          stroke="url(#gradient)"
          strokeWidth="4"
          >
          </Path>
      </Svg>
    );
  }
}

const samples = [SvgLayoutExample, Issue178];

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
        <TestCase itShould="Issue#178: Stroke color should have linear gradient">
          <Issue178 />
        </TestCase>
      </ScrollView>
    </Tester>
  );
}
