import { RNPackage, TurboModulesFactory } from '@rnoh/react-native-openharmony/ts';
import type { TurboModule, TurboModuleContext } from '@rnoh/react-native-openharmony/ts';
import { RNSVGSvgViewModule } from './RNSVGSvgViewModule';
import { RNSVGRenderableModule } from './RNSVGRenderableModule';
import { RNSVGImageModule } from './RNSVGImageModule';

class SvgTurboModulesFactory extends TurboModulesFactory {
  createTurboModule(name: string): TurboModule | null {
    if (name === 'RNSVGSvgViewModule') {
      return new RNSVGSvgViewModule(this.ctx);
    }
    if (name === 'RNSVGRenderableModule') {
      return new RNSVGRenderableModule(this.ctx);
    }
    if (name === 'RNSVGImageModule') {
      return new RNSVGImageModule(this.ctx);
    }
    return null;
  }

  hasTurboModule(name: string): boolean {
    return name === 'RNSVGSvgViewModule' || name === 'RNSVGRenderableModule' || name === 'RNSVGImageModule';
  }
}

export class SvgPackage extends RNPackage {
  createTurboModulesFactory(ctx: TurboModuleContext): TurboModulesFactory {
    return new SvgTurboModulesFactory(ctx);
  }
}