import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genStrokeProps, genFillProps } from '../genUtil'
const basicProps = {
    cx: '50',
    cy: '50',
    r: '30',
}

const allCases = [
    ...genFillProps(),
    ...genStrokeProps(),
    ...genTransformProps()
]


function GenCircle () {
    return <GenMain
                cases={allCases}
                basicProps={basicProps}
                comName='Circle'
            />
}

export default GenCircle