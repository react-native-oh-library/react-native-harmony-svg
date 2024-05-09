import React from "react";
// import  from 'react-native-svg'
import { Circle, Rect } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genStrokeProps, genFillProps, CaseParams } from '../genUtil'
const basicProps = {
    width: '100',
    height: '100',
    viewBox: '0 0 100 100'
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        values: [
            {
                width: 30,
                height: 60,
                viewBox: '0 0 100 100'
            },
            {
                width: 90,
                height: 60,
                fill: 'green',
                viewBox: '0 0 200 100'
            },
        ]
    }
]

const allCases = [
    ...basicCases,
    ...genFillProps(),
]


export default function () {
    return (
        <GenMain
            cases={allCases}
            basicProps={basicProps}
            comName='Svg'
            noSvg={true}
            renderComChildren={<Circle cx="50" cy="50" r="40" />}
        >
        </GenMain>
    )
}