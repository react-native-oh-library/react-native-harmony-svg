import React, { Component } from 'react';
import { StyleSheet, ScrollView, View } from 'react-native';
import {
  Svg,
  Circle,
  Path,
  Rect,
  Mask,
  RNSVGMask,
  Polygon,
  Defs,
  LinearGradient,
  Stop,
  Text,
  Pattern,
  Ellipse
} from 'react-native-svg';
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';

const styles = StyleSheet.create({
  container: {
    height: 300,
    width: 200,
    marginBottom: 10,
  },
  svg: {
    flex: 1,
    alignSelf: 'stretch',
  },
});

class SimplePattern extends Component {
    static title = 'Simple svg with pattern';
    render() {
      return (
        <Svg width={225} height={225} >    
            <Defs>    
            <Pattern id="Triangle" width={10} height={10} patternUnits="userSpaceOnUse" viewBox="0 0 10 10">    
                <Circle cx={10} cy={10} r={5}  fill="red"/>    
                </Pattern>    
            </Defs>    
            <Circle cx={50} cy={50} r={50}  fill="url(#Triangle)"/>    
            <Circle cx={50} cy={150} r={50} />    
        </Svg>
      );
    }
}

class PatternWithViewBox extends Component {
  static title = 'pattern svg with viewbox';
  render() {
    return (
        <View style={styles.container}>
            <Svg width="100%" height="100%" viewBox="0 0 800 400">
                <Defs>
                <Pattern
                    id="TrianglePattern"
                    patternUnits="userSpaceOnUse"
                    x={0}
                    y={0}
                    width={100}
                    height={100}>
                    <Path d="M 0 0 L 7 0 L 3.5 7 z" fill="red" stroke="blue" />
                </Pattern>
                </Defs>
                <Rect fill="none" stroke="blue" x={1} y={1} width={798} height={398} />
                <Ellipse
                fill="url(#TrianglePattern)"
                stroke="black"
                strokeWidth={5}
                cx={400}
                cy={200}
                rx={350}
                ry={150}
                />
            </Svg>
        </View>
    );
  }
}

class PatternWithTransform extends Component {
  static title = 'pattern svg with viewbox';
  render() {
    return (
        <View style={styles.container}>
            <Svg viewBox="0 0 100 100">
            <Pattern
              id="p1"
              patternUnits="userSpaceOnUse"
              width="20"
              height="20"
              patternTransform="rotate(20)
                      skewX(30)
                      scale(1 0.5)"
            >
            <Circle cx="10" cy="10" r="10" />
            </Pattern>
            <Rect x="10" y="10" width="80" height="80" fill="url(#p1)" />
          </Svg>
        </View>
    );
  }
}

const samples = [SimplePattern, PatternWithViewBox, PatternWithTransform];

export { samples };

export default function () {
  return (
    <Tester style={{
      display: 'flex',
      flexDirection: 'column'
    }}>
      <ScrollView>
        <TestCase itShould="SimplePattern">
          <SimplePattern />
        </TestCase>
        <TestCase itShould="PatternWithViewBox">
          <PatternWithViewBox />
        </TestCase>
        <TestCase itShould="PatternWithTransform">
          <PatternWithTransform />
        </TestCase>
      </ScrollView>
    </Tester>
  )
}