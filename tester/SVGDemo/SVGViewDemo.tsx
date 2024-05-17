import React, {Component} from 'react';
import {ScrollView, Text, View, Button} from 'react-native';
import Svg, {
  Path,
  RNSVGMask,
  Rect,
  Image,
  Circle,
  Polygon,
  LinearGradient,
  Stop,
  Defs,
  RNSVGSvgIOS,
  G,
  Line,
} from 'react-native-svg';

class GExample extends Component {
  static title = 'G children props inherit';
  state = {
    fill: 'purple',
  };
  render() {
    return (
      <View>
        <Button
          title="change state"
          onPress={() => {
            if (this.state.fill == 'purple') {
              this.setState({
                fill: 'green',
              });
            } else if (this.state.fill == 'green') {
              this.setState({
                fill: 'purple',
              });
            }
          }}
        />
        <Svg height="100" width="100">
          <G stroke="pink" strokeWidth="3">
            <Circle cx="75" cy="75" r="11" fill={this.state.fill} />
          </G>
        </Svg>
      </View>
    );
  }
}

const SVGDemo = () => {
  return (
    <View>
      <View style={{height: 100}} />
      {/* <Svg height="100" width="100">
          <Path
            d="M25 10 L98 65 L70 25 L16 77 L11 30 L0 4 L90 50 L50 10 L11 22 L77 95 L20 25"
            fill="none"
            stroke="red"
            strokeWidth="1"
          />
        </Svg> */}

      <Svg height="200" width="200">  
        <Path  
          d="M110 10 L190 10 L190 90 Q170 50 150 90 Z"  
          stroke="black"  
          strokeWidth="10"  
          strokeMiterlimit="2" // 斜接限制较低，可能会看到斜角连接  
          fill="none"  
        />  
        <Path  
          d="M110 120 L190 120 L190 190 Q170 150 150 190 Z"  
          stroke="black"  
          strokeWidth="10"  
          strokeMiterlimit="10" // 斜接限制较高，可能会看到更长的斜接  
          fill="none"  
        />  
      </Svg>  
      {/* <GExample /> */}
    </View>
  );
};

export default SVGDemo;
