import React from "react";
// import  from 'react-native-svg'
import { Svg, Circle, Polygon } from 'react-native-svg'
import { GenDefs } from './gen'
import { genTransformProps, genFillProps, genStrokeProps, CaseParams } from '../genUtil'
const basicProps = {
    id: 'star',
    viewBox: '0,0,10,10',
    width: '10%',
    height: '10%'
}
// id="star" viewBox="0,0,10,10" width="5%" height="5%"

const basicCases: CaseParams[] = [
    {
        type: 'mulKey',
        id: 'pattern1',
        values: [
            {
                width: '10%',
                height: '10%'
            },
            {
                width: '5%',
                height: '5%'
            },
            {
                width: '25%',
                height: '25%'
            },
        ]
    },
    {
        key: 'patternTransform',
        values: ['skewX(20) translate(-35, 0)', 'translate(5, 6)', 'scale(1, 4)', 'rotate(30)', 'skewX(20)', 'skewY(20)']
    }
]

const allCases = [
    ...basicCases,
    ...genTransformProps()
]

const EffectCom = (
    <Circle cx="50" cy="50" r="50" fill="url(#star)" />
)
const DefChildren = (
    <Polygon points="0,0 2,5 0,10 5,8 10,10 8,5 10,0 5,2" />
)

export default function () {
    return (
        <GenDefs
            cases={allCases}
            basicProps={basicProps}
            renderComChildren={DefChildren}
            EffectCom={EffectCom}
            defName="Pattern"
        >
        </GenDefs>
    )
}