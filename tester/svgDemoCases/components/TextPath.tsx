import React from "react";
import { Svg, Text, TextPath, Path, Defs, G } from 'react-native-svg'
import { ScrollView, View } from 'react-native'
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function () {
    return (
        <Svg viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg">
            <G stroke="blue">
                <Path
                    id="MyPath"
                    fill="none"
                    stroke="red"
                    d="M10,90 Q90,90 90,45 Q90,10 50,10 Q10,10 10,40 Q10,70 45,70 Q70,70 75,50" />

                <Text color="white" stroke="blue" fill="blue" fontVariant="small-caps" fontStretch="ultra-expanded" fontVariationSettings={"XHGT 0.7"}>
                <TextPath stroke="blue" fill="blue" href="#MyPath">Quick brown fox jumps over the lazy dog.</TextPath>
            </Text>
        </G>
        </Svg >

    )
}