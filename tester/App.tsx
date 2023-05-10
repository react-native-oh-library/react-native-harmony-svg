import React from 'react';
import {StyleSheet, View} from 'react-native';
import SVG from 'react-native-harmony-svg';
import {Tester, TestSuite, TestCase} from '@rnoh/testerino';

function App({}): JSX.Element {
  return (
    <View style={styles.container}>
      <Tester>
        <TestSuite name="react-native-svg">
          <TestCase itShould="render sth...">
            <SVG style={styles.svgContainer} />
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
