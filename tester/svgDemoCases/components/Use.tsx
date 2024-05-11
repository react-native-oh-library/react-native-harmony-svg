import React from "react";
import { Svg, Circle, Use, Defs, G, Symbol} from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import {Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function () {
    return (
        <Tester style={{ flex: 1 }}>
            <ScrollView>
                <TestCase
                    itShould="case 1: move x "
                >
                    <View style={{
                                    borderWidth: 1,
                                    width: 100,
                                    height: 100
                                }}
                    >
                        <Svg viewBox="0 0 400 400">
                            <Circle id="shape" cx="100" cy="100" r="50" stroke="black" />
                            <Use href="#shape" x="200" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase
                    itShould="case 2: move y "
                >
                    <View style={{
                                    borderWidth: 1,
                                    width: 100,
                                    height: 100
                                }}
                    >
                        <Svg viewBox="0 0 400 400">
                            <Circle id="shape" cx="100" cy="100" r="50" stroke="black" />
                            <Use href="#shape" y="200" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase
                    itShould="case 3: change opacity"
                >
                    <View style={{
                                    borderWidth: 1,
                                    width: 100,
                                    height: 100
                                }}
                    >
                        <Svg viewBox="0 0 400 400">
                            <Circle id="shape" cx="100" cy="100" r="20" strokeWidth="8" stroke="black" fill="black" opacity="1" />
                            <Circle  cx="140" cy="100" r="20" strokeWidth="8" stroke="black" fill="black" opacity="0.8" />
                            <Circle  cx="180" cy="100" r="20" strokeWidth="8" stroke="black" fill="black" opacity="0.6" />
                            <Circle  cx="220" cy="100" r="20" strokeWidth="8" stroke="black" fill="black" opacity="0.4" />

                            <Use href="#shape" x="100" y="160" />
                            <Use href="#shape" x="140" y="160" fill="black" opacity="0.8" />
                            <Use href="#shape" x="180" y="160" fill="black" opacity="0.6" />
                            <Use href="#shape" x="220" y="160" fill="black" opacity="0.4" />
                        </Svg>
                    </View>
                </TestCase>

            </ScrollView>
        </Tester>
    )
}