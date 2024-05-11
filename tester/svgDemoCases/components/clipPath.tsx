import React from "react";
import { Svg, Circle, ClipPath, Rect, Path, Use, Defs, G } from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function () {
    return (
        <Tester style={{ flex: 1 }}>
            <ScrollView>

                <TestCase itShould="Attribute: clipPath=Rect">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <Rect x="5" y="5" width="80" height="80" fill="green" />
                            <Rect x="35" y="25" width="80" height="80" fill="red" />

                            <ClipPath id="myClip" clipRule="evenodd">
                                <Rect x="155" y="5" width="80" height="80" fill="green" />
                            </ClipPath>
                            <Rect x="185" y="25" width="80" height="80" fill="red" clipPath="url(#myClip)" />
                        </Svg>
                    </View>
                </TestCase>

                {/* <TestCase itShould="Attribute: clipRule=nonzero">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" id="star1" clipRule="nonzero" />
                            </ClipPath>
                            <ClipPath id="emptyStar2" >
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" id="star2" clipRule="nonzero" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar)" width="50" height="90" fill="blue" />
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" />
                        </Svg>

                    </View>
                </TestCase> */}

                {/* <TestCase itShould="Attribute: clipRule=evenodd">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar" clipRule="evenodd">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" id="star1" clipRule="evenodd" />
                            </ClipPath>
                            <ClipPath id="emptyStar2" clipRule="evenodd">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" id="star2" clipRule="evenodd" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar)" width="50" height="90" fill="blue" clipRule="evenodd"/>
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" clipRule="evenodd"/>
                        </Svg>

                    </View>
                </TestCase> */}

            </ScrollView>
        </Tester >
    )
}