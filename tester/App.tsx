import React from 'react';
import {StyleSheet, View} from 'react-native';
import Svg, {Path} from 'react-native-harmony-svg';
import {Tester, TestSuite, TestCase} from '@rnoh/testerino';

function App({}): JSX.Element {
  return (
    <View style={styles.container}>
      <Tester>
        <TestSuite name="react-native-svg">
          <TestCase itShould="display black triangle">
            <Svg style={styles.svgContainer} viewBox="0 0 100 100">
              <Path d="M50 0 L15 100 L85 100 Z" />
            </Svg>
          </TestCase>
        </TestSuite>
      </Tester>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    width: '100%',
    height: '100%',
  },
  svgContainer: {
    width: '100%',
    height: 300,
  },
});

export default App;
