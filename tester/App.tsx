/* eslint-disable react-native/no-inline-styles */
import React, {useEffect, useState} from 'react';
import {ScrollView, StyleSheet, View} from 'react-native';
import Svg, {
  Path,
  G,
  Rect,
  Circle,
  ClipPath,
  Defs,
  Image,
  LinearGradient,
  Stop,
} from 'react-native-svg';
import {Tester, TestSuite, TestCase} from '@rnoh/testerino';
import QRCode from 'react-native-qrcode-svg';

const TRIANGLE_PATH_DATA = 'M64 0 L0 128 L128 128 Z';

function App({}): JSX.Element {
  return (
    <ScrollView style={styles.container}>
      <Tester>
        <TestSuite name="react-native-svg">
          <TestCase itShould="display black triangle">
            <Svg style={styles.svgContainer}>
              <Path d={TRIANGLE_PATH_DATA} />
            </Svg>
          </TestCase>
          <TestCase itShould="display red triangle with orange border on blue background">
            <Svg style={[styles.svgContainer, {backgroundColor: 'blue'}]}>
              <Path
                d={TRIANGLE_PATH_DATA}
                fill="red"
                stroke="orange"
                strokeWidth={8}
              />
            </Svg>
          </TestCase>
          <TestCase itShould="[FAILS] change triangle color every second">
            <Blinker
              renderContent={refreshKey => {
                return (
                  <Svg
                    style={[styles.svgContainer, {backgroundColor: 'white'}]}>
                    <Path
                      d={TRIANGLE_PATH_DATA}
                      fill={refreshKey % 2 ? 'red' : 'black'}
                      stroke="orange"
                      strokeWidth={8}
                    />
                  </Svg>
                );
              }}
            />
          </TestCase>
          <TestCase itShould="display a smaller triangle on the right">
            <View style={[styles.svgContainer, {flexDirection: 'row'}]}>
              <Svg style={{width: '50%', backgroundColor: 'red'}}>
                <Path d={TRIANGLE_PATH_DATA} />
              </Svg>
              <Svg
                style={{width: '50%', backgroundColor: 'blue'}}
                viewBox="0 0 500 100">
                <Path d={TRIANGLE_PATH_DATA} />
              </Svg>
            </View>
          </TestCase>
          <TestCase itShould="display red rectangle with green border (G)">
            <Svg style={styles.svgContainer}>
              <G fill="red" stroke="green" strokeWidth={8}>
                <Path d={TRIANGLE_PATH_DATA} />
              </G>
            </Svg>
          </TestCase>
          <TestCase itShould="render semi-transparent red rectangle with a pink border">
            <Svg style={styles.svgContainer}>
              <Rect
                fill="red"
                width="100"
                height="100"
                stroke="pink"
                strokeWidth="8"
                opacity="0.5"
              />
            </Svg>
          </TestCase>
          <TestCase itShould="render semi-transparent red circle with a pink border">
            <Svg style={styles.svgContainer}>
              <Circle
                cy="50"
                cx="50"
                r="50"
                fill="red"
                stroke="pink"
                strokeWidth="8"
                opacity="0.5"
              />
            </Svg>
          </TestCase>
          <TestCase itShould="display a red circle in a blue rectangle">
            <Svg style={styles.svgContainer}>
              <Defs>
                <ClipPath id="clip-circle">
                  <Circle cy="50" cx="50" r="50" />
                </ClipPath>
              </Defs>
              <Rect
                fill="blue"
                width="100"
                height="100"
                stroke="pink"
                strokeWidth="8"
              />
              <Rect
                fill="red"
                width="100"
                height="100"
                stroke="pink"
                strokeWidth="8"
                clipPath="url(#clip-circle)"
              />
            </Svg>
          </TestCase>
          {/* Path to the image must be transformed to make this component work.  */}
          <TestCase
            itShould="export image component"
            fn={({expect}) => {
              expect(Image).not.to.be.undefined;
            }}
          />
          <TestCase itShould="[FAILS] support linear gradient">
            {/* props may yet need to be transformed e.g. supporting various fill's ColorStruct types. */}
            <Svg style={styles.svgContainer}>
              <Svg height="150" width="300">
                <Defs>
                  <LinearGradient id="grad" x1="0" y1="0" x2="1" y2="0">
                    <Stop offset="0" stopColor="#FFD080" stopOpacity="1" />
                    <Stop offset="1" stopColor="red" stopOpacity="1" />
                  </LinearGradient>
                </Defs>
                <Circle cy="50" cx="50" r="50" fill="url(#grad)" />
              </Svg>
            </Svg>
          </TestCase>
          <TestCase itShould="make react-native-qrcode-svg usable">
            <QRCode value="123" />
          </TestCase>
        </TestSuite>
      </Tester>
    </ScrollView>
  );
}

function Blinker(props: {renderContent: (refreshKey: number) => any}) {
  const [refreshKey, setRefreshKey] = useState(0);

  useEffect(() => {
    const id = setInterval(() => {
      setRefreshKey(prev => prev + 1);
    }, 1000);
    return () => {
      clearInterval(id);
    };
  }, []);

  return <>{props.renderContent(refreshKey)}</>;
}

const styles = StyleSheet.create({
  container: {
    width: '100%',
    height: '100%',
  },
  svgContainer: {
    width: '100%',
    height: 128,
  },
});

export default App;
