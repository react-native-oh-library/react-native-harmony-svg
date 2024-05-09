


import React, {  } from 'react'
import { View, Text as QText, ScrollView } from 'react-native'
import { Svg } from 'react-native-svg';
import * as ASVG from 'react-native-svg'
import {Tester, Filter, TestCase, TestSuite } from '@rnoh/testerino';
import { CaseParams } from '../genUtil'

export interface RenderCaseProps{
    _case: CaseParams,
    basicProps: Object,
    comName: string,
    children?: React.ReactNode,
    bindFunc?: Object
    renderComChildren?: React.ReactNode | string,
    noSvg?: boolean
}

function deepMerge<T extends object, U extends object>(  
    obj1: T,  
    obj2: U,  
    mergeValues: boolean = true // 默认值为true，表示要合并值  
): T & U {  
    const result: any = { ...obj1 }; // 浅拷贝obj1到result  
  
    // 遍历obj2的属性  
    for (const key in obj2) {  
        if (obj2.hasOwnProperty(key)) { 
            //@ts-ignore
            const val1 = obj1[key];  
            const val2 = obj2[key];  
  
            // 如果mergeValues为false，则不合并值，直接跳过  
            if (!mergeValues) {  
                continue;  
            }  
  
            // 如果两个值都是对象，则递归合并  
            if (val1 && typeof val1 === 'object' && val2 && typeof val2 === 'object') {  
                result[key] = deepMerge(val1, val2, mergeValues);  
            } else {  
                // 否则，直接覆盖  
                result[key] = val2;  
            }  
        }  
    }  
  
    return result as T & U;  
}  

function RenderCase({_case, basicProps, comName, renderComChildren, bindFunc, noSvg, ...props} : RenderCaseProps) {
    const type = _case.type || 'key-value'
    return (
        <View
            style={{
                backgroundColor: '#000'
            }}
            key={_case.id || _case.key || JSON.stringify(_case.values)}
        >
            {
                (_case.values || []).map((v, i) => {
                    //@ts-ignore
                    const Com = ASVG[comName]
                    const caseProps = type === 'key-value' ? {[_case.key as string]: v } : v
                    let showProps = deepMerge(caseProps, _case.othersProps || {}, _case.showOtherProps)
                    const word = type === 'key-value' ? `${_case.key}=${v}` : `${JSON.stringify(showProps)}`
                    return (
                        <TestCase
                        // <View
                            itShould={`${_case.desc || word}`}
                            key={JSON.stringify(v) + _case.key + _case.id}
                        >
                            <View
                                style={{
                                    borderWidth: 1,
                                    width: 100,
                                    height: 100
                                }}
                            >
                                {
                                    noSvg ? 
                                    <Com
                                        {...basicProps} 
                                        { ..._case.othersProps }
                                        {...caseProps }
                                        { ...bindFunc }
                                    >
                                        {renderComChildren}
                                    </Com>
                                :
                                    <Svg width={'100%'} height={'100%'}>
                                        <Com
                                            {...basicProps} 
                                            { ..._case.othersProps }
                                            {...caseProps }
                                            { ...bindFunc }
                                        >
                                            {renderComChildren}
                                        </Com>
                                    </Svg>
                                }
                                
                            </View>
                        </TestCase>
                    )
                })
            }
        </View>
    )
}
export interface GenMainProps{
    cases: CaseParams[],
    basicProps: Object,
    comName: string,
    children?: React.ReactNode,
    bindFunc?: Object
    renderComChildren?: React.ReactNode | string,
    noSvg?: boolean
}
export function GenMain({
    cases,
    basicProps,
    comName,
    children,
    bindFunc,
    renderComChildren,
    noSvg
} : GenMainProps) {
    return (
        <Tester style={{flex: 1}}>
             <ScrollView>
                {
                    cases.map(_case => {
                        return (
                            <RenderCase _case={_case}
                                basicProps={basicProps}
                                comName={comName}
                                key={_case.key}
                                renderComChildren={renderComChildren}
                                bindFunc={bindFunc}
                                noSvg={noSvg}
                            />
                        )
                    })
                }
                { children }
            </ScrollView>
        </Tester>
    )
}

export function GenDefs() {
    return (
        <Tester style={{flex: 1}}>
            <ScrollView>

            </ScrollView>
        </Tester>
    )
}