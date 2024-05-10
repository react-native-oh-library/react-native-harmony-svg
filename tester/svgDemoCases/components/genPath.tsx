import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps, genStrokeProps, CaseParams } from '../genUtil'
const basicProps = {
    d: "M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z"
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        values: [
            {
                opacity: '0.1'
            },
            {
                opacity: '0.6'
            },
            {
                d:`M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z`,
                fill: 'red'
            }
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
            comName='Path'
        />
}