import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle, Rect } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genStrokeProps, genFillProps, CaseParams } from '../genUtil'
const basicProps = {
    width: 80,
    height: 80,
    href: 'data:image/png;base64,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'
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        id: 'image1',
        values: [
            {
                width: 80,
                height: 80,
                opacity: '1'
            },
            {
                width: 80,
                height: 80,
                opacity: '0.1'
            },
            {
                width: 30,
                height: 60,
                opacity: '0.5'
            },
            {
                width: 90,
                height: 60,
                fill: 'green'
            },
            {
                width:90,
                height: 60,
                fill: 'red',
                xlinkHref: "https://img.icons8.com/2266EE/search"
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
    return (
        <GenMain
            cases={allCases}
            basicProps={basicProps}
            comName='Image'
        >
        </GenMain>
    )
}