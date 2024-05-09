import React from 'react';

import {
    SafeAreaView,
    ScrollView,
    StatusBar,
    StyleSheet,
    Text,
    useColorScheme,
    View,
    TouchableOpacity,
} from 'react-native';
import { useNavigation } from '@react-navigation/native';

const styles = StyleSheet.create({
    item: {
        padding: 20,
        backgroundColor: 'rgba(0, 0, 0, 0.7)',
        color: '#fff',
        borderColor: 'rgba(0, 0, 0, 0.6)',
        borderBottomWidth: 2,
    }
})

interface ItemProps {
    name: never | string,
    title: string
}

function Item({ name, title }: ItemProps){
    const navigation = useNavigation();
    return (
        <TouchableOpacity onPress={() => {
            navigation.navigate(name as never)
        }}>
            <View style={styles.item}>
                <Text
                    style={{ color: '#fff' }}
                >{title}</Text>
            </View>
        </TouchableOpacity>
    )
}

let routers = [
    {
        name: 'oldDemo',
        title: 'oldDemo'
    },
    {
        name: 'Xml',
        title: 'Xml'
    },
    {
        name: 'genCircle',
        title: 'Circle'
    },
    {
        name: 'genEllise',
        title: 'Ellise'
    },
    {
        name: 'genPath',
        title: 'Path'
    },
    {
        name: 'genPolygon',
        title: 'Polygon'
    },
    {
        name: 'genPolyline',
        title: 'Polyline'
    },
    {
        name: 'genRect',
        title: 'Rect'
    },
    {
        name: 'G',
        title: 'G'
    },
    {
        name: 'Line',
        title: 'Line'
    },
    {
        name: 'genText',
        title: 'Text'
    },
    {
        name: 'Mask',
        title: 'Mask'
    },
    {
        name: 'TouchEvents',
        title: 'TouchEvents'
    },
    {
        name: 'Defs',
        title: 'Defs'
    },
    {
        name: 'ForeignObject',
        title: 'ForeignObject'
    },
    {
        name: 'genTSpan',
        title: 'TSpan'
    },
    {
        name: 'LinearGradient',
        title: 'LinearGradient'
    },
    {
        name: 'Marker',
        title: 'Marker'
    },
    {
        name: 'Pattern',
        title: 'Pattern'
    },
    {
        name: 'RadialGradient',
        title: 'RadialGradient'
    },
    {
        name: 'Symbol',
        title: 'Symbol'
    },
    {
        name: 'TextPath',
        title: 'TextPath'
    },
    {
        name: 'Use',
        title: 'Use'
    },
    {
        name: 'genSvg',
        title: 'Svg'
    }
]
routers.sort((a: ItemProps, b: ItemProps) => {
    return a.title.localeCompare(b.title)
})

export default function () {
    return (
        <ScrollView
            style={{
                backgroundColor: 'rgba(0, 0, 0, 0.7)'
            }}
        >
            {
                routers.map(router => {
                    return <Item name={router.name as never} title={router.title}  key={router.name}/>
                })
            }
        </ScrollView>
    )
}