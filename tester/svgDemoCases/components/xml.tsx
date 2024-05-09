import React from "react"
import { View, Text, StyleSheet } from 'react-native'
import { SvgAst, SvgFromUri, SvgFromXml, SvgXml, Circle, SvgUri, parse, Svg, AstProps, JsxAST } from 'react-native-svg'
const css = StyleSheet.create({
    item: {
        backgroundColor: '#fff',
        marginBottom: 4,
        padding: 6
    },
    svgBorder: {
        borderWidth: 1
    }
})

interface ItemProps{
    text: string,
    children: React.ReactNode
}

function Item({ text, children }: ItemProps) {
    return (
        <View
            style={[css.svgBorder, css.svgBorder]}
        >
            <Text>{text}</Text>
            {children}
        </View>
    )
}

export default function () {
    const xmlCase = `
        <svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
        width="500px" height="500px" viewBox="0 0 500 500" enable-background="new 0 0 500 500" xml:space="preserve">
        <circle cx="50%" cy="50%" r="40%" fill="pink" />
        </svg>
    `
    return (
        <View style={{
            padding: 10,
            paddingTop: 20,
        }}>
            <Item
                text="test SvgUri"
            >
                <SvgUri
                    width="150"
                    height="70"
                    uri="https://dev.w3.org/SVG/tools/svgweb/samples/svg-files/debian.svg"
                />
            </Item>
            <Item
                text="test SvgFromUri"
            >
                <SvgFromUri
                    width="150"
                    height="70"
                    uri="https://dev.w3.org/SVG/tools/svgweb/samples/svg-files/debian.svg"
                />
            </Item>
            <Item text="test SvgXml">
                <SvgXml xml={xmlCase} width="100" height="100" />
            </Item>
            <Item text="test parse">
                <Svg width={60} height={60}>
                    {(parse(xmlCase) as JsxAST).children}
                </Svg>
            </Item>
            <Item text="test SvgFromXml">
                <SvgFromXml xml={xmlCase} width="90" height="70" />
            </Item>
            <Item text="test SvgAst">
                <SvgAst ast={parse(xmlCase)} override={{ width: "60", height: "70" }}  />
            </Item>
        </View>
    )
}