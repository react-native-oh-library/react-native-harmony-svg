import React, { Component, useState } from 'react';
import Svg, {
  Circle,
  Ellipse,
  G,
  Text as SVGText,
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
  SvgXml,
} from 'react-native-svg';
import { View, StyleSheet, ScrollView, Text, Button } from 'react-native';
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';

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
      <Svg style={{ height: 200, width: 374.1538391113281 }}>
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
          strokeWidth="4"></Path>
      </Svg>
    );
  }
}

class Issue185 extends Component {
  static title = 'Stroke LinearGradient';
  render() {
    return (
      <Svg style={{ height: 200, width: 200 }}>
        <Path
          d="M 5 2,h 154,q 3 0 3 3,v 164,q 0 3 -3 3,h -154,q -3 0 -3 -3,v -164,q 0 -3 3 -3"
          fill="rgba(3,102,214,0.2)"></Path>
      </Svg>
    );
  }
}

class Issue193 extends Component {
  static title = 'Mask with LinearGradient';
  svgXml = `<svg width="240" height="240" viewBox="0 0 240 240" fill="none"
  xmlns="http://www.w3.org/2000/svg">
  <circle cx="120" cy="120" r="120" fill="#FFECDE"/>
  <mask id="mask0_14651_25129" style="mask-type:alpha" maskUnits="userSpaceOnUse" x="0" y="0" width="240" height="240">
  <rect width="240" height="240" rx="30" fill="#FF00DC"/>
  </mask>
  <g mask="url(#mask0_14651_25129)">
  <path fill-rule="evenodd" clip-rule="evenodd" d="M57.1418 157.143C57.1418 169.767 67.3753 180 79.999 180H159.999C172.623 180 182.856 169.767 182.856 157.143V97.1429H57.1418V157.143ZM57.1419 85.7143H182.856L169.147 68.5784C164.81 63.1563 158.243 60 151.299 60H88.699C81.7554 60 75.1882 63.1563 70.8506 68.5784L57.1419 85.7143ZM82.2853 147.429C78.4982 147.429 75.4281 150.499 75.4281 154.286C75.4281 158.073 78.4982 161.143 82.2853 161.143H116.571C120.358 161.143 123.428 158.073 123.428 154.286C123.428 150.499 120.358 147.429 116.571 147.429H82.2853Z" fill="url(#paint0_linear_14651_25129)"/>
  </g>
  <defs>
  <linearGradient id="paint0_linear_14651_25129" x1="57.1418" y1="180" x2="177.032" y2="54.4397" gradientUnits="userSpaceOnUse">
  <stop stop-color="#FF003A"/>
  <stop offset="1" stop-color="#FF0056"/>
  </linearGradient>
  </defs>
  </svg>`;
  render() {
    return <SvgXml xml={this.svgXml} width={240} height={240} />;
  }
}

class Issue203 extends Component {
  static title = 'Stroke LinearGradient';
  static data = [
    [0, 2, 4],
    [0, 6, 12, -6, -12, -18, -24],
    [0, 3, 6, 9, -3, -6],
  ];
  static index = 0;
  constructor(props) {
    super(props);
    this.state = {
      dataY: Issue203.data[0],
    };
  }

  render() {
    return (
      <View style={{ magrinTop: 100 }}>
        <View style={{ display: 'flex', height: 200, flexDirection: 'row' }}>
          <View style={{ padding: 20 }}>
            <Text>RN Text</Text>
            {this.state.dataY.map((value, index) => {
              return <Text key={value + index}>{value}</Text>;
            })}
          </View>
          <View style={{ padding: 20 }}>
            <Text>RNSVG Text</Text>
            <Svg
              style={{
                position: 'absolute',
                top: 40,
                left: 0,
                height: 300,
                width: 180,
              }}>
              <G>
                {this.state.dataY.map((value, index) => {
                  return (
                    <SVGText
                      textAnchor={'middle'}
                      x={'30%'}
                      alignmentBaseline={'middle'}
                      key={value}
                      y={index * 20}>
                      {value}
                    </SVGText>
                  );
                })}
              </G>
            </Svg>
          </View>
        </View>
        <Button
          title="切换"
          onPress={() => {
            this.setState({ dataY: Issue203.data[Issue203.index] });
            Issue203.index = (Issue203.index + 1) % 3;
          }}>
          切换
        </Button>
      </View>
    );
  }
}

export function Issue203Extend() {
  const [dataX, setDataX] = useState(25);
  return (
    <View>
      <Svg height="100" width="100%">
        <Rect
          x={dataX}
          y="70"
          width="50"
          height="25"
          fill="rgb(0,0,255)"
          strokeWidth="3"
          stroke="red"
        />
        <Circle
          cx={dataX}
          cy="25"
          r="25"
          stroke="purple"
          strokeWidth="2.5"
          fill="none"
        />
      </Svg>
      <Button title="切换" onPress={() => {
        let data = dataX + 5 < 300 ? dataX + 5 : 25;
        setDataX(dataX + 5)
      }}>切换</Button>
    </View>
  );
}

const samples = [SvgLayoutExample, Issue178, Issue185, Issue193, Issue203, Issue203Extend];

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
    <Tester style={{ flex: 1 }}>
      <ScrollView>
        <TestCase itShould="SVG with flex layout">
          <SvgLayoutExample />
        </TestCase>
        <TestCase itShould="Issue#178: Stroke color should have linear gradient">
          <Issue178 />
        </TestCase>
        <TestCase itShould="Issue #185: The <Path d='M 5 2,h 154,q 3 0 3 3,v 164,q 0 3 -3 3,h -154,q -3 0 -3 -3,v -164,q 0 -3 3 -3'> should draw properly">
          <Issue185 />
        </TestCase>
        <TestCase itShould="Issue #193: Box with window surrounded by circle">
          <Issue193 />
        </TestCase>
        <TestCase itShould="Issue #203: The content of RNSVG Text should display as same as the RN Text">
          <Issue203 />
        </TestCase>
        <TestCase itShould="Issue #203 extend: The path should not repeat display">
          <Issue203Extend />
        </TestCase>
      </ScrollView>
    </Tester>
  );
}
