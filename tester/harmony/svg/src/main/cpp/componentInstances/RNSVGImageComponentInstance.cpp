/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGImageComponentInstance.h"
#include "turboModules/RNSVGImageModule.h"

namespace rnoh {
namespace svg {

RNSVGImageComponentInstance::RNSVGImageComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)),
      ImageSourceResolver::ImageSourceUpdateListener(
          (std::dynamic_pointer_cast<RNSVGImageModule>(m_deps->rnInstance.lock()->getTurboModule("RNSVGImageModule")))
              ->getImageSourceResolver()) {
    SetSvgNode(m_svgImage);
}

void RNSVGImageComponentInstance::UpdateElementProps() {
    if (m_deps != nullptr && !m_deps->rnInstance.expired()) {
        auto rnInstance = m_deps->rnInstance.lock();
        if (rnInstance != nullptr) {
            auto nativeResourceManager = rnInstance->getNativeResourceManager();
            m_svgImage->setNativeResourceManager(nativeResourceManager);
        }
    }
    m_svgImage->UpdateCommonProps(m_props);
    m_svgImage->SetX(m_props->x);
    m_svgImage->SetY(m_props->y);
    m_svgImage->SetWidth(m_props->width);
    m_svgImage->SetHeight(m_props->height);
    m_svgImage->SetAlign(m_props->align);
    m_svgImage->SetMeetOrSlice(m_props->meetOrSlice);
    m_svgImage->SetImageSource(m_src);
}

void RNSVGImageComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    if (!m_props || m_props->src != props->src) {
        if (!props->src.uri.empty() && props->src.uri.find("http", 0) != 0) {
            // 非网络资源
            m_src.uri = props->src.uri;
            return;
        }
        std::string cacheDir = FindLocalCacheByUri(props->src.uri);
        if (!cacheDir.empty()) {
            DLOG(INFO) << "[SVGImage] hit cache: " << cacheDir;
            m_src.uri = cacheDir;
        }
    }
};

std::string RNSVGImageComponentInstance::FindLocalCacheByUri(std::string const &uri) {
    // 非网络资源，直接返回uri
    if (uri.find("http", 0) != 0) {
        return uri;
    }

    auto rnInstance = m_deps->rnInstance.lock();
    if (!rnInstance) {
        return uri;
    }

    auto turboModule = rnInstance->getTurboModule("RNSVGImageModule");
    if (!turboModule) {
        return uri;
    }

    auto arkTsTurboModule = std::dynamic_pointer_cast<RNSVGImageModule>(turboModule);
    if (!arkTsTurboModule || !arkTsTurboModule->getImageSourceResolver()) {
        LOG(ERROR) << "[SVGImage] FastImageSourceResolver is unavailable!";
        return uri;
    }

    // 查找缓存目录
    auto basePtr = shared_from_this();
    auto thisPtr = std::static_pointer_cast<RNSVGImageComponentInstance>(basePtr);
    auto cacheDir = arkTsTurboModule->getImageSourceResolver()->resolveImageSources(thisPtr, uri);

    if (!cacheDir.empty()) {
        return cacheDir; // 如果找到缓存文件，返回缓存路径
    }
    // 否则开始下载
    arkTsTurboModule->downloadImage(uri, {});
    return ""; // 返回空字符串，表示下载未完成或缓存未命中
}

void RNSVGImageComponentInstance::onImageSourceCacheUpdate(std::string imageUri) {
    LOG(INFO) << "[SVGImage] onImageSourceCacheUpdate, uri: " << imageUri;
    m_src.uri = imageUri;
    onFinalizeUpdates();
};

void RNSVGImageComponentInstance::onImageSourceCacheDownloadFileFail() {
    LOG(ERROR) << "[SVGImage] ImageSource download fail!";
};

} // namespace svg
} // namespace rnoh
