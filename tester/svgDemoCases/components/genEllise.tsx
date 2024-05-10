import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps, CaseParams } from '../genUtil'
const basicProps = {
    cx: 50,
    cy: 50,
    rx: 50,
    ry: 30
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        values: [
            {
                cx: 30,
                cy: 60,
                
            },
            {
                cx: 90,
                cy: 60,
                fill: 'red'
            },
            {
                cx: 30,
                cy: 60,
                rx: 20,
                ry: 30,
                opacity: '0.3'
            },
            {
                cx: 30,
                cy: 60,
                rx: 20,
                ry: 40,
            },
        ],
        othersProps: {
            fill: 'green'
        },
    }
]


const allCases = [
    ...basicCases,
    ...genFillProps(),
    ...genTransformProps()
]

export default function () {
    return <GenMain
                cases={allCases}
                basicProps={basicProps}
                comName='Ellipse'
            />
}