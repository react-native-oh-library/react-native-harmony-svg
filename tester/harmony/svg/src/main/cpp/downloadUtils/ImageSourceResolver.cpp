/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include <fstream>
#include "ImageSourceResolver.h"

namespace rnoh {
namespace svg {

std::string ImageSourceResolver::resolveImageSources(std::shared_ptr<ImageSourceUpdateListener> listener, std::string uri) {
    // 判断是否还在下载中
    if (m_pendingSet.find(uri) != m_pendingSet.end()) {
        removeListener(listener);
        addListenerForURI(uri, listener);
        return "";
    }
    // 生成图像的哈希缓存文件名
    auto hashedFileName = StringUtils::generateHashedFileName(uri);

    bool exist = remoteImageSourceMap_.get(hashedFileName);
    if (exist) {
        auto cacheUri = "file://" + fileCacheDir_ + hashedFileName;
        return cacheUri;
    }
    removeListener(listener);
    addListenerForURI(uri, listener);
    return "";
}

void ImageSourceResolver::addListenerForURI(const std::string &uri, std::shared_ptr<ImageSourceUpdateListener> listener) {
    listener->observedUri = uri;
    auto it = m_uriListenersMap.find(uri);
    if (it == m_uriListenersMap.end()) {
        m_uriListenersMap.emplace(uri, std::vector<std::weak_ptr<ImageSourceUpdateListener>>{listener});
        return;
    }

    auto alreadyThere = std::find_if(it->second.begin(), it->second.end(),[&listener]  
    (const std::weak_ptr<ImageSourceUpdateListener> &wk )
    {   
        auto sp = wk.lock();
        return sp == listener;

    });
    if (alreadyThere != it->second.end())
    {
        return;
    }
    it->second.push_back(listener);
}

void ImageSourceResolver::removeListenerForURI(const std::string &uri, std::shared_ptr<ImageSourceUpdateListener> listener) {
    auto it = m_uriListenersMap.find(uri);
    if (it == m_uriListenersMap.end()) {
        return;
    }
    auto &listeners = it->second;
    auto listenerPos = std::find_if(listeners.begin(), listeners.end(), [&listener](const std::weak_ptr<ImageSourceUpdateListener> &wk)
    {
        auto sp = wk.lock();
        return sp == listener;

    });
    if (listenerPos != listeners.end()) {
        listeners.erase(listenerPos);
        if (listeners.empty()) {
            m_uriListenersMap.erase(uri);
        }
    }
}

void ImageSourceResolver::removeListener(std::shared_ptr<ImageSourceUpdateListener> listener) {
    if (!listener->observedUri.empty()) {
        removeListenerForURI(listener->observedUri, listener);
    }
}

void ImageSourceResolver::imageDownloadComplete(std::string uri, std::string fileUri) {
    auto pend = m_pendingSet.find(uri);
    if (pend != m_pendingSet.end()) {
        m_pendingSet.erase(uri);
    }
    // 生成图像的哈希缓存文件名
    auto hashedFileName = StringUtils::generateHashedFileName(uri);
    DLOG(INFO) << "[SVGImage] remoteImageSourceMap PUT: " << hashedFileName;
    remoteImageSourceMap_.put(hashedFileName, true);
    auto it = m_uriListenersMap.find(uri);
    if (it == m_uriListenersMap.end()) {
        return;
    }

    auto &listeners = it->second;
    for (auto listener : listeners) {

        if (auto weaklistener = listener.lock())
        {
            weaklistener->onImageSourceCacheUpdate(fileUri);
            removeListenerForURI(uri, weaklistener);
        }

    }
}

void ImageSourceResolver::imageDownloadFail(std::string uri) {
    auto pend = m_pendingSet.find(uri);
    if (pend != m_pendingSet.end()) {
        m_pendingSet.erase(uri);
    }

    auto it = m_uriListenersMap.find(uri);
    if (it == m_uriListenersMap.end()) {
        return;
    }
    auto &listeners = it->second;
    for (auto listener : listeners) {

        auto weaklistener = listener.lock();
        weaklistener->onImageSourceCacheDownloadFileFail();
        removeListenerForURI(uri, weaklistener);
    }
}


} // namespace svg
} // namespace rnoh