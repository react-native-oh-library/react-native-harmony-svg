import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps } from '../genUtil'
const basicProps = {
    cx: 50,
    cy: 50,
    rx: 50,
    ry: 30
}

const allCases = [
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