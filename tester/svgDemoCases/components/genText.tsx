import React from "react";
// import  from 'react-native-svg'
import { Svg, TSpan } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps , genStrokeProps, CaseParams } from '../genUtil'
const basicProps = {
    x: 10,
    y: 20
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        id: 'text1',
        values: [
            {
                x: 10,
                y: 20
            },
            {
                x: 10,
                y: 20,
                dx: 10
            },
            {
                x: 10,
                y: 20,
                dx: 10,
                dy: 30
            },
        ]
    }
]

const allCases = [
    ...basicCases,
    ...genFillProps(),
    ...genStrokeProps(),
    ...genTransformProps()
]


export default function () {
    return <GenMain
                cases={allCases}
                basicProps={basicProps}
                comName='Text'
                renderComChildren={<TSpan>Test Text</TSpan>}
            >
            </GenMain>
}