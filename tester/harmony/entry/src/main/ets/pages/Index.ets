import {
  RNApp,
  ComponentBuilderContext,
  RNOHCoreContext,
  MetroJSBundleProvider,
  RNOHErrorDialog
} from '@rnoh/react-native-openharmony'

let storage = LocalStorage.GetShared()

@Builder
function CustomComponentBuilder(ctx: ComponentBuilderContext) {
  Stack() {
  }
}

const wrappedCustomRNComponentBuilder = wrapBuilder(CustomComponentBuilder)

@Entry(storage)
@Component
struct Index {
  @StorageLink('RNOHCoreContext') rnohCoreContext: RNOHCoreContext | undefined = undefined

  build() {
    Column() {
      if (this.rnohCoreContext) {
        RNOHErrorDialog({ ctx: this.rnohCoreContext });
        RNApp({
          appKey: "app_name",
          rnInstanceConfig: {
            enableCAPIArchitecture: true,
            createRNPackages: (ctx) => []
          },
          buildCustomComponent: CustomComponentBuilder,
          jsBundleProvider: new MetroJSBundleProvider(),
          wrappedCustomRNComponentBuilder: wrappedCustomRNComponentBuilder,
        })
      }
    }
    .height('100%')
    .width('100%')
  }
}
