/* eslint-disable @typescript-eslint/ban-types */
// its needed for codegen to work
import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  getBase64String(uri: string): Promise<string>;
}

export default TurboModuleRegistry.get<Spec>('RNSVGImageModule')!;
