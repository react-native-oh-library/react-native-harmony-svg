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
                    <Svg>
                        <Symbol id="sym01" viewBox="0 0 150 110">
                            <Circle cx="50" cy="50" r="40" strokewidth="8" stroke="red" fill="red" />
                            <Circle
                                cx="90"
                                cy="60"
                                r="40"
                                strokewidth="8"
                                stroke="green"
                                fill="white" />
                        </Symbol>

                        <Use href="#sym01" x="0" y="0" width="100" height="50" />
                        <Use href="#sym01" x="0" y="50" width="75" height="38" />
                        <Use href="#sym01" x="0" y="100" width="50" height="25" />
                    </Svg>
                </TestCase>
            </ScrollView>
        </Tester>
    )
}