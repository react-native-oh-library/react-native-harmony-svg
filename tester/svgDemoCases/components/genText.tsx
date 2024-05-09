import React from "react";
// import  from 'react-native-svg'
import { Svg, TSpan } from 'react-native-svg'
import { GenMain } from './gen'
import { genTransformProps, genFillProps , genStrokeProps} from '../genUtil'
const basicProps = {
    x: 10,
    y: 20
}

const allCases = [
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