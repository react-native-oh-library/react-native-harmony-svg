import React from "react";
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genTouchableProps, genFillProps, CaseParams } from '../genUtil'
const basicProps = {
    width: 80,
    height: 80,
    fill: 'red'
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        values: [
            {
                width: 30,
                height: 60
            },
            {
                width: 90,
                height: 60,
                fill: 'green'
            },
        ]
    }
]


const allCases: CaseParams[] = [
    ...basicCases,
    ...genFillProps(),
    ...genTransformProps(),
]

const bindFunc = {
    ...genTouchableProps('Rect')
}


export default function () {
    return (
        <GenMain
            cases={allCases}
            basicProps={basicProps}
            comName='Rect'
            bindFunc={bindFunc}
        />
    )
}