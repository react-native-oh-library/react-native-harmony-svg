/* eslint-disable react-native/no-inline-styles */
import React, {useEffect, useState} from 'react';
import {ScrollView, StyleSheet, View} from 'react-native';
import Svg, {Path, G, Rect} from 'react-native-svg';
import {Tester, TestSuite, TestCase} from '@rnoh/testerino';

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
          <TestCase itShould="[FAILS] display smaller right triangle">
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
          <TestCase itShould="[FAILS] change triangle color every second">
            <Blinker
              renderContent={refreshKey => {
                return (
                  <Svg
                    style={[styles.svgContainer, {backgroundColor: 'white'}]}>
                    <Path
                      d={TRIANGLE_PATH_DATA}
                      fill={refreshKey % 2 ? 'red' : 'black'}
                    />
                  </Svg>
                );
              }}
            />
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
