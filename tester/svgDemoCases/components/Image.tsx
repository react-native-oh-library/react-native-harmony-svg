import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle, Rect } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genStrokeProps, genFillProps, CaseParams } from '../genUtil'
const basicProps = {
    width: 80,
    height: 80,
    href: 'https://live.mdnplay.dev/zh-CN/docs/Web/SVG/Element/image/mdn_logo_only_color.png'
}

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
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
        ]
    }
]

const allCases = [
    ...basicCases,
    // ...genFillProps(),
    // ...genStrokeProps(),
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