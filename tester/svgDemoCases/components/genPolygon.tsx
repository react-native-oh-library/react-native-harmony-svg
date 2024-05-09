import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps } from '../genUtil'
const basicProps = {
    points: "40,5 70,80 25,95"
}

const allCases = [
    ...genFillProps(),
    ...genTransformProps()
]


export default function () {
    return <GenMain
                cases={allCases}
                basicProps={basicProps}
                comName='Polygon'
            />
}