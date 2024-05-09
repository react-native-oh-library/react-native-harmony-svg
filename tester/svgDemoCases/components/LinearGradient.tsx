import React from "react";
import { Svg, Circle,  } from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import {Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function() {
    return (
        <Tester style={{flex: 1}}>
             <ScrollView>
                <TestCase 
                    itShould=""
                >
                    <View>
                        <Text>a test case in here</Text>
                    </View>
                </TestCase>
            </ScrollView>
        </Tester>
    )
}