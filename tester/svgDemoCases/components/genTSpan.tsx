import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps, genStrokeProps, CaseParams } from '../genUtil'
const basicProps = {
    x: 10,
    y: 20
}


const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        id: 'tspan1',
        values: [
            {
                x: 10,
                y: 10
            },
            {
                dx: 20,
                dy: 30,
                fill: 'green'
            },
            {
                rotate: '45',
            },
            {
                inlineSize: '6'
            }
        ]
    }
]

const allCases = [
    ...basicCases,
    // ...genFillProps(),
    ...genStrokeProps(),
    // ...genTransformProps()
]


export default function () {
    return (
        <GenMain
            cases={allCases}
            basicProps={basicProps}
            comName='TSpan'
            renderComChildren="测试文本"
        >
        </GenMain>
    )
}