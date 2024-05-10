import React from "react";
import { ScrollView, Text, View } from 'react-native';
import Svg, {
    Rect,
    Circle,
    Marker,
    G,
    Line,
} from 'react-native-svg';
import { Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
export default function () {
    return (

        <View>
            <Svg viewBox="0 0 600 500" width={400} height={400} color="green" preserveAspectRatio="xMinYMid slice">
                <Marker
                    id="arrow"
                    viewBox="0 0 10 10"
                    refX="5"
                    refY="5"
                    markerWidth="6"
                    markerHeight="6"
                    orient="auto-start-reverse">
                    <Rect
                        x="0"
                        y="0"
                        width="10"
                        height="10"
                        fill="red"
                    />
                </Marker>
                <G stroke="pink" fill="pink" strokeWidth={10} opacity="0.5">
                    <Rect
                        x="50"
                        y="50"
                        width="180"
                        height="170"
                        stroke="currentColor"
                        fill="yellow"
                        strokeDashoffset={10}
                        strokeLinecap="round"
                        strokeLinejoin="bevel"
                        rx="20"
                        ry="40"
                    />
                    <Circle
                        cx="50"
                        cy="50"
                        r="45"
                        stroke="blue"
                        strokeWidth="2.5"
                        fill="green"
                        mask="url(#myMask)"
                    />
                    <Line
                        x1="30"
                        y1="40"
                        x2="200"
                        y2="180"
                        stroke="grey"
                        strokeWidth={10}
                        strokeLinecap="round"
                        strokeLinejoin="bevel"
                        markerStart="url(#arrow)"
                        markerMid="url(#arrow)"
                        markerEnd="url(#arrow)"
                    />
                    <Line
                        x1="30"
                        y1="70"
                        x2="300"
                        y2="70"
                        stroke="blue"
                        strokeDasharray="20 10"
                    />
                    <Line
                        x1="30"
                        y1="110"
                        x2="300"
                        y2="110"
                        stroke="blue"
                        strokeDasharray="20 10 30"
                    /></G>
            </Svg>
        </View>
    );
};