import React from "react";
import { Svg, Circle, ClipPath, Rect, Path, Use, Defs, G, } from 'react-native-svg'
import { ScrollView, View, Text } from 'react-native'
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function () {
    return (
        <Tester style={{ flex: 1 }}>
            <ScrollView>

                <TestCase itShould="Attribute: clipPath=Red rect">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <Rect x="5" y="5" width="80" height="80" fill="green" />
                            <Rect x="35" y="25" width="80" height="80" fill="red" />

                            <ClipPath id="myClip1">
                                <Rect x="185" y="25" width="80" height="80" />
                            </ClipPath>
                            <Rect x="155" y="5" width="80" height="80" fill="green" clipPath="url(#myClip1)" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase itShould="Attribute: clipPath=Green rect">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <Rect x="5" y="5" width="80" height="80" fill="green" />
                            <Rect x="35" y="25" width="80" height="80" fill="red" />

                            <ClipPath id="myClip2">
                                <Rect x="155" y="5" width="80" height="80" />
                            </ClipPath>
                            <Rect x="185" y="25" width="80" height="80" fill="red" clipPath="url(#myClip2)" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase itShould="Attribute: clipRule=default/evenodd(L) + default/evenodd(R)">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar1">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>
                            <ClipPath id="emptyStar2">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar1)" width="50" height="90" fill="blue" />
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase itShould="Attribute: clipRule=evenodd(L) + evenodd(R)">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar1" clipRule="evenodd">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>
                            <ClipPath id="emptyStar2" clipRule="evenodd">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar1)" width="50" height="90" fill="blue" />
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase itShould="Attribute: clipRule=nonzero(L) + nonzero(R)">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar1" clipRule="nonzero">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>
                            <ClipPath id="emptyStar2" clipRule="nonzero">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar1)" width="50" height="90" fill="blue" />
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase itShould="Attribute: clipRule=evenodd(L) + nonzero(R)">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar1" clipRule="evenodd">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>
                            <ClipPath id="emptyStar2" clipRule="nonzero">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar1)" width="50" height="90" fill="blue" />
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" />
                        </Svg>
                    </View>
                </TestCase>

                <TestCase itShould="Attribute: clipRule=nonzero(L) + evenodd(R)">
                    <View style={{
                        borderWidth: 1, width: 400, height: 120
                    }}>
                        <Svg>
                            <ClipPath id="emptyStar1" clipRule="nonzero">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>
                            <ClipPath id="emptyStar2" clipRule="evenodd">
                                <Path d="M50,0 21,90 98,35 2,35 79,90z" />
                            </ClipPath>

                            <Rect clipPath="url(#emptyStar1)" width="50" height="90" fill="blue" />
                            <Rect clipPath="url(#emptyStar2)" width="50" height="90" x="50" fill="red" />
                        </Svg>
                    </View>
                </TestCase>

            </ScrollView >
        </Tester >
    )
}