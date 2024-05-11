import React from "react";
import { Svg, Circle, SvgFromXml, Use, Symbol } from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
import { opacity } from "react-native-reanimated/lib/typescript/reanimated2/Colors";
import { transformer } from "../../metro.config";
export default function () {
    return (
    <Tester style={{ flex: 1 }}>
        <ScrollView>
        <TestCase
            itShould="case 1: display symbol with use "
        >
            <View style={{
                            borderWidth: 1,
                            width: 100,
                            height: 100
                        }}
            >
                <Svg viewBox="0 0 400 400">
                    <Circle id="shape" cx="100" cy="100" r="20" fill="black" />

                    <Use href="#shape" x="200" y="200" fill="blue" />
                </Svg>
            </View>
        </TestCase>

        <TestCase
            itShould="case 2: TODO: dismatch while use viewbox"
        >
            <View style={{
                            borderWidth: 1,
                            width: 100,
                            height: 100
                        }}
            >
                <Svg viewBox="0 0 400 400">
                <Symbol id="symbol" viewBox="0 0 150 110" width="100" height="50">
                    <Circle cx="50" cy="50" r="40" strokeWidth="8" stroke="red" fill="red" />
                    <Circle
                    cx="90"
                    cy="60"
                    r="40"
                    strokeWidth="8"
                    stroke="green"
                    fill="white"
                    />
                </Symbol>
                    <Use href="#symbol" x="0" y="0" />
                    <Use href="#symbol" x="0" y="50" width="75" height="38" />
                    <Use href="#symbol" x="0" y="100" width="50" height="25" />
                </Svg>
            </View>
        </TestCase>
        </ScrollView>
    </Tester>
    )
}