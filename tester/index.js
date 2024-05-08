/**
 * @format
 */

import {AppRegistry} from 'react-native';
import App from './App';
import SVGDemo from './SVGDemo/SVGViewDemo';
import {name as appName} from './app.json';

// AppRegistry.registerComponent(appName, () => App);
AppRegistry.registerComponent(appName, () => SVGDemo);
