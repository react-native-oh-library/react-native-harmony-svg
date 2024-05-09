
import React from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  View,
} from 'react-native';
import {NavigationContainer, Page} from './Navigation';
import {PortalHost, PortalProvider} from '@gorhom/portal';
import testSuiteByName from './components';
import {Tester} from '@rnoh/testerino';
console.log(`testSuiteByName:`, testSuiteByName)

function App() {
    return (
      <View style={{backgroundColor: 'black'}}>
        <StatusBar barStyle="light-content" />
        <SafeAreaView>
          <NavigationContainer>
            <PortalProvider>
              {Object.keys(testSuiteByName).map(testSuiteName => {
                const TestSuite =
                  testSuiteByName[testSuiteName as keyof typeof testSuiteByName];
                return (
                  <Page
                    key={testSuiteName}
                    name={`${testSuiteName.replace('Test', '')}`}>
                    {/* <Tester style={{flex: 1}}>
                      <ScrollView style={{flex: 1}}> */}
                        <TestSuite key={testSuiteName} />
                      {/* </ScrollView>
                    </Tester> */}
                  </Page>
                );
              })}
              
            </PortalProvider>
          </NavigationContainer>
        </SafeAreaView>
      </View>
    );
  }
  export default App