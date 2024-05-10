import React from "react";
import { Svg, Circle, SvgFromXml } from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
import { opacity } from "react-native-reanimated/lib/typescript/reanimated2/Colors";
import { transformer } from "../../metro.config";
export default function () {
    return (
        <Tester style={{ flex: 1 }}>
            <ScrollView>
                <TestCase
                    itShould="case 1 desc"
                >
                    <Text>case 1 in here</Text>
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