import { Alert, View, Text } from 'react-native'
export interface CaseParams {
    type?: | 'mulKey' | 'key-value' | undefined,
    id?: string,
    key?: string,
    values?: string[] | Object[],
    title?: string,
    desc?: string,
    othersProps?: Object,
    showOtherProps?: boolean,
    showBasicProps?: boolean,
    opacity?:string
}

export function genFillProps() {
    return [

        {
            key: 'fill',
            values: ['#000', 'pink', 'green', 'red'],
            title: '测试fill属性',
        },
        {
            key: 'fillOpacity',
            values: ['0.15', '0.5', '1'],
            title: '测试fillOpacity属性'
        },
        {
            key: 'fillRule',
            values: ['evenodd', 'nonzero'], // 'evenodd' | 'nonzero'
            othersProps: {
                fill: 'green'
            }
        },
    ]
}

export function commonProps() {
    return [
        {
            key: 'opacity',
            values: ['0.1', '0.5', '1']
        },
    ]
}

export function genStrokeProps(): CaseParams[] {
    return [
        {
            key: 'stroke',
            values: ['#000', 'red', 'green'],
            othersProps: {}
        },
        {
            key: 'strokeWidth',
            values: ['1', '4', '8'],
            othersProps: {
                stroke: 'green'
            }
        },
        {
            key: 'strokeOpacity',
            values: ['0.1', '0.5', '1'],
            othersProps: {
                stroke: 'green',
                strokeWidth: '8',
            }
        },
        {
            key: 'strokeDasharray',
            values: ['5, 5', '20, 20'],
            othersProps: {
                stroke: 'green',
                strokeWidth: '8',
            }
        },
        {
            key: 'strokeDashoffset',
            values: ['10', '50', '80'],
            othersProps: {
                stroke: 'green',
                strokeWidth: '8',
                strokeDasharray: "20 20"
            }
        },
        {
            key: 'strokeLinecap',
            values: ['butt', 'round', 'square'],
            othersProps: {
                stroke: 'green',
                strokeWidth: 8,
                y: 20,
                x: 10
            }
        },
        {
            key: 'strokeLinejoin',
            values: ['miter', 'bevel', 'round'],
            othersProps: {
                stroke: 'green',
                strokeWidth: 8,
            }
        },
        {
            key: 'strokeMiterlimit',
            values: ['10', '20', '30'],
            othersProps: {
                stroke: 'green',
                strokeWidth: '8',
            }
        },
        {
            key: 'vectorEffect',
            values: ['none', 'non-scaling-stroke', 'nonScalingStroke', 'default', 'uri', 'inherit'],
            othersProps: {
                stroke: 'green',
                strokeWidth: '8',
            }
        },
    ]
}
`
stroke?: ColorValue
strokeWidth?: NumberProp
strokeOpacity?: NumberProp
strokeDasharray?: ReadonlyArray<NumberProp> | NumberProp
strokeDashoffset?: NumberProp
strokeLinecap?: Linecap
strokeLinejoin?: Linejoin
strokeMiterlimit?: NumberProp
vectorEffect?: VectorEffect

vectorEffect?:
    | 'none'
    | 'non-scaling-stroke'
    | 'nonScalingStroke'
    | 'default'
    | 'inherit'
    | 'uri'
`

export function genClipProps(): CaseParams[] {
    return [
        {
            key: 'clipRule',
            values: ['evenodd', 'nonzero']
        },
        // {
        //     key: 'clipPath',
        //     values: []
        // }
    ]
}
export function genTransformProps(): CaseParams[] {
    return [
        {
            key: 'translate',
            values: ['10', '20', '30']
        },
        {
            key: 'translateX',
            values: ['10', '20', '30']
        },
        {
            key: 'translateY',
            values: ['10', '20', '30']
        },
        {
            key: 'origin',
            values: ['0, 0', '30, 30', '60, 60'],
            othersProps: {
                rotation: '45'
            },
            showOtherProps: true
        },
        {
            key: 'scale',
            values: ['0.7', '1', '2']
        },
        {
            key: 'scaleX',
            values: ['0.7', '1', '2']
        },
        {
            key: 'scaleY',
            values: ['0.7', '1', '2']
        },
        {
            key: 'rotation',
            values: ['0', '45', '-45', '60']
        },
        {
            key: 'x',
            values: ['10', '20', '30']
        },
        {
            key: 'y',
            values: ['10', '20', '30']
        },
        {
            key: 'transform',
            values: ['translate(10, 10)', 'scale(2)', 'rotate(45)']
        },
    ]
}
`
translate?: NumberArray
translateX?: NumberProp
translateY?: NumberProp
origin?: NumberArray
originX?: NumberProp
originY?: NumberProp
scale?: NumberArray
scaleX?: NumberProp
scaleY?: NumberProp
rotation?: NumberProp
x?: NumberArray
y?: NumberArray
transform?:
    | ColumnMajorTransformMatrix
    | string
    | TransformsStyle['transform']
`

export function genResponderProps(): CaseParams[] {
    return [
        {
            key: 'pointerEvents',
            values: ['box-none', 'none', 'box-only', 'auto']
        },
    ]
}
`
pointerEvents?: 'box-none' | 'none' | 'box-only' | 'auto'
`

export function genTouchableProps(name: string, { disabled = false } = {}) {
    return {
        disabled,
        onPress () {
            console.log(`Triggered onPress of the ${name}`)
            Alert.alert(`Triggered onPress of the ${name}`)
        },
        onPressIn () {
            console.log(`Triggered onPressIn of the ${name}`)
        },
        onLongPress() {
            console.log(`Triggered onLongPress of the ${name}`)
        },
        onPressOut() {
            console.log(`Triggered onPressOut of the ${name}`)
        },
        delayPressIn: 1000,
        delayPressOut: 1000
    }
}

export function genAccessibilityProps(): CaseParams[] {
    return [
        {
            key: 'testID',
            values: []
        },
        {
            key: 'accessible',
            values: ['true', 'false']
        },
        {
            key: 'accessibilityLabel',
            values: ['video', 'music', 'news'],
            othersProps: {
                accessible: 'true'
            },
            showOtherProps: true
        },
    ]
}

export function genViewProps(): CaseParams[] {
    return [
        {
            key: 'style',
            values: [
                {
                    opacity: '0.1'
                }
            ]
        },
        {
            key: 'hitSlop',
            values: [
                {
                    top: 0,
                    left: 0,
                    bottom: 0,
                    right: 0
                },
                {
                    top: 0,
                    left: 0,
                    bottom: 0,
                    right: 0
                },
                {
                    top: 0,
                    left: 0,
                    bottom: 0,
                    right: 0
                },
            ]
        },
        {
            key: 'hitSlop',
            values: []
        },
        {
            key: 'hitSlop',
            values: []
        },
        {
            key: 'hitSlop',
            values: []
        },
        {
            key: 'hitSlop',
            values: []
        },
        {
            key: 'hitSlop',
            values: []
        },
        {
            key: 'hitSlop',
            values: []
        },
    ]
}

export function genViewPropsFuncs(name: string) {
    return {
    }
}

export function genCommonPathProps(): CaseParams[] {
    return [
        {
            key: 'opacity',
            values: ['0.1', '0.5', '1']
        },
        ...genFillProps(),
        ...genStrokeProps(),
        ...genTransformProps(),
        ...genAccessibilityProps()
    ]
}
`
| 'baseline'
| 'text-bottom'
| 'alphabetic'
| 'ideographic'
| 'middle'
| 'central'
| 'mathematical'
| 'text-top'
| 'bottom'
| 'center'
| 'top'
| 'text-before-edge'
| 'text-after-edge'
| 'before-edge'
| 'after-edge'
| 'hanging';
`
export function genTextSpecificProps(): CaseParams[] {
    return [
        {
            key: 'alignmentBaseline',
            values: ['baseline', 'text-bottom', 'alphabetic', 'ideographic', 'middle', 'central', 'mathematical', 'text-top', 'bottom', 'center', 'top', 'text-before-edge', 'text-after-edge', 'before-edge', 'after-edge', 'hanging']
        },
        {
            key: 'baselineShift',
            values: ['sub', 'super', 'baseline']
        },
        {
            key: 'verticalAlign',
            values: ['baseline', 'top', 'middle', 'bottom', 'sub', 'text-top']
        },
        {
            key: 'lengthAdjust',
            values: ['spacing', 'spacingAndGlyphs']
        },
        {
            key: 'textLength',
            values: ['5', '10', '150%']
        },
        {
            key: 'fontData',
            values: ['']
        },
        {
            key: 'fontFeatureSettings',
            values: ['normal', '"liga" 0', 'tnum', 'smcp']
        },
    ]
}

export function genFontProps(): CaseParams[] {
    return [
        {
            key: 'fontWeight',
            values: ['normal', 'bold', 'bolder', 'lighter'],
            othersProps: {
                fontSize: '18'
            }
        },
        {
            key: 'fontSize',
            values: ['12', '24', '48']
        },
        {
            key: 'fontFamily',
            values: ['Verdana', 'Times'],
            othersProps: {
                fontSize: '30',
                y: 60
            }
        },
        {
            key: 'textAnchor',
            values: ['start', 'middle', 'end'] // 'start' | 'middle' | 'end'
        },
        {
            key: 'letterSpacing',
            values: ['1', '4', '10']
        },
        {
            key: 'wordSpacing',
            values: ['1', '4', '10']
        },
        {
            key: 'fontStyle',
            values: ['normal', 'italic', 'oblique']
        }
    ]
}

export function genTextCommonProps() {

}

export function genAdditionalProps(name: string) {
    return {
        onError() {
            console.log(`Triggered onError of the ${name}`)
            Alert.alert(`Triggered onError of the ${name}`)
        },
        onLoad() {
            console.log(`Triggered onLoad of the ${name}`)
        },
        fallback() {
            return <Text>this is fallback</Text>
        }
    }
}

export function genPointerEvents() {

}

export function genCommonMarkerProps() {

}