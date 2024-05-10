
import React from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  View,
} from 'react-native';
// import * as exampleByName from './components';
import {NavigationContainer, Page} from './Navigation';
// import {Benchmarker, DeepTree, SierpinskiTriangle} from './benchmarks';
import {PortalHost, PortalProvider} from '@gorhom/portal';
import testSuiteByName from './components';
import {Tester} from '@rnoh/testerino';


const comList = Object.keys(testSuiteByName).map(testSuiteName => {
  return {
    name: testSuiteName,
    com: testSuiteByName[testSuiteName as keyof typeof testSuiteByName]
  }
})
// @ts-ignore
comList.sort((a, b) => {
  return a.name.localeCompare(b.name)
})

function App() {
    return (
      <View style={{backgroundColor: 'black'}}>
        <StatusBar barStyle="light-content" />
        <SafeAreaView>
          <NavigationContainer>
            <PortalProvider>
              {comList.map(com => {
                const TestSuite = com.com
                return (
                  <Page
                    key={com.name}
                    name={`${com.name.replace('Test', '')}`}>
                    {/* <Tester style={{flex: 1}}>
                      <ScrollView style={{flex: 1}}> */}
                        <TestSuite key={com.name} />
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