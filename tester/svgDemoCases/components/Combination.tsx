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

class CircleRectPathExample extends Component {
  static title = 'Path shaped marker on line';
  render() {
    return (
      <Svg height="100" width="100">
        <Rect x="0" y="0" width="100" height="100" fill="black" />
        <Circle cx="50" cy="50" r="30" fill="yellow" />
        <Circle cx="40" cy="40" r="4" fill="black" />
        <Circle cx="60" cy="40" r="4" fill="black" />
        <Path d="M 40 60 A 10 10 0 0 0 60 60" stroke="black" />
      </Svg>
    );
  }
}

class CurrentColorExample extends Component {
  static title = 'Line Path use currentColor';
  render() {
    return (
      <Svg
        width="130"
        height="130"
        fill="blue"
        stroke="red"
        color="green"
        viewBox="-16 -16 544 544">
        <Path
          d="M318.37,85.45L422.53,190.11,158.89,455,54.79,350.38ZM501.56,60.2L455.11,13.53a45.93,45.93,0,0,0-65.11,0L345.51,58.24,449.66,162.9l51.9-52.15A35.8,35.8,0,0,0,501.56,60.2ZM0.29,497.49a11.88,11.88,0,0,0,14.34,14.17l116.06-28.28L26.59,378.72Z"
          strokeWidth="32"
        />
        <Path d="M0,0L512,512" stroke="currentColor" strokeWidth="32" />
      </Svg>
    );
  }
}

class SvgG extends Component {
  static title = 'Line Path use currentColor';
  render() {
    return (
      <Svg height="100" width="200">
        <G rotation="50" origin="100, 50">
          <Line x1="60" y1="10" x2="140" y2="10" stroke="#060" />
          <Rect
            x="60"
            y="20"
            height="50"
            width="80"
            stroke="#060"
            fill="#060"
          />
          <Text x="100" y="75" stroke="#600" fill="#600" textAnchor="middle">
            Text grouped with shapes
          </Text>
        </G>
      </Svg>
    );
  }
}

class GExample extends Component {
    static title = 'G children props inherit';
    state = {
      fill: 'purple',
    };
    componentDidMount = () => {
      setTimeout(() => {
        if (!this._unmounted) {
          this.setState({
            fill: '#856',
          });
        }
      }, 2000);
    };
    componentWillUnmount = () => {
      this._unmounted = true;
    };
    private _unmounted: any;
    render() {
      return (
        <Svg height="100" width="100">
          <G fill={this.state.fill} stroke="pink" strokeWidth="3">
            <Circle cx="25" cy="25" r="11" />
            <Circle cx="25" cy="75" r="11" stroke="red" />
            <Circle cx="50" cy="50" r="11" fill="green" />
            <Circle cx="75" cy="25" r="11" stroke="red" />
            <Circle cx="75" cy="75" r="11" />
          </G>
        </Svg>
      );
    }
  }

const samples = [SvgLayoutExample, CircleRectPathExample, CurrentColorExample, SvgG, GExample];

const styles = StyleSheet.create({
  container: {
    flex: 1,
    height: 100,
    width: 200,
    backgroundColor: "red"
  },
  svg: {
    height: "80%",
    width: "80%",
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
        {/* <TestCase itShould="Blue fill, Red stroke pen and Green Line">
          <CurrentColorExample />
        </TestCase>
        <TestCase itShould="Rect, Circle, Path">
          <CircleRectPathExample />
        </TestCase>
        <TestCase itShould="Text Rect Line Parallel">
          <SvgG />
        </TestCase>
        <TestCase itShould="GExample">
          <GExample />
        </TestCase> */}
      </ScrollView>
    </Tester>
  );
}
