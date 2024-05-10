import React from "react";
import { Svg, Circle, Use, Defs, G} from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import {Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function () {
    return (
        <Svg>
            <Circle  cx="50" cy="50" r="50" fill="black" />

            <Defs>
                <G id ="shape1">
                    <Circle  cx="200" cy="200" r="50" fill="black" />
                </G>
            </Defs>

            <Use href="#shape1" x="100" y="100" />
        </Svg>
    )
}