import React from "react";
import { Svg, Circle, SvgFromXml } from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import {Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
const testxml = `<svg
viewBox="0 0 10 10"
xmlns="http://www.w3.org/2000/svg"
xmlns:xlink="http://www.w3.org/1999/xlink">
<defs>
  <linearGradient id="myGradient" gradientTransform="rotate(90)">
    <stop offset="5%" stop-color="gold" />
    <stop offset="95%" stop-color="red" />
  </linearGradient>
</defs>

<!-- using my linear gradient -->
<circle cx="5" cy="5" r="4" fill="url(#myGradient)" />
</svg>`
export default function() {
    return (
        <Tester style={{flex: 1}}>
             <ScrollView>
                <TestCase 
                    itShould="case 1 desc"
                >
                    <SvgFromXml 
                        width={'100%'}
                        height={'100%'}
                        xml={testxml}
                    />
                </TestCase>
                <TestCase 
                    itShould="case 2 desc"
                >
                    <Text>case 2 in here</Text>
                </TestCase>
            </ScrollView>
        </Tester>
    )
}