/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <memory>
#include <unordered_set>
#include <filesystem>
#include "RNOH/RNInstance.h"
#include "downloadUtils/LRUCache.h"
#include "utils/StringUtils.h"

namespace fs = std::filesystem;

namespace rnoh {
namespace svg {

// ImageSourceResolver 类用于管理图像源的缓存与下载
class ImageSourceResolver {
public:
    using Shared = std::shared_ptr<ImageSourceResolver>;

    // 构造函数，初始化缓存目录以及设置LRU缓存
    explicit ImageSourceResolver(std::string fileCacheDir)
        : m_uriListenersMap(), fileCacheDir_(fileCacheDir),
          remoteImageSourceMap_(128, [this](std::string fileUri, bool a) {
              // 删除缓存文件（LRU缓存淘汰回调）
              fs::path filePath = this->fileCacheDir_ + fileUri;
              if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
                  LOG(INFO) << "[SVGImage] remoteImageSourceMap delete: " << filePath;
                  return fs::remove(filePath);
              }
              return false;
          }) {}

    // 图像源更新的监听器基类
    class ImageSourceUpdateListener {
    public:
        std::string observedUri; // 监听的图像URI

        ImageSourceUpdateListener(ImageSourceResolver::Shared const &ImageSourceResolver)
            : m_imageSourceResolver(ImageSourceResolver) {}

        // 注销监听器
        ~ImageSourceUpdateListener() = default;

        // 监听图像缓存更新
        virtual void onImageSourceCacheUpdate(std::string imageUri) = 0;

        // 监听图像下载失败
        virtual void onImageSourceCacheDownloadFileFail() = 0;

    private:
        ImageSourceResolver::Shared const &m_imageSourceResolver;
    };

    // 解析图像源的缓存路径
    std::string resolveImageSources(std::shared_ptr<ImageSourceUpdateListener> listener, std::string uri);

    // 为URI添加监听器
    void addListenerForURI(const std::string &uri, std::shared_ptr<ImageSourceUpdateListener> listener);

    // 从URI移除监听器
    void removeListenerForURI(const std::string &uri, std::shared_ptr<ImageSourceUpdateListener> listener);

    // 从解析器中移除监听器
    void removeListener(std::shared_ptr<ImageSourceUpdateListener> listener);

    // 下载完成后更新图像缓存
    void imageDownloadComplete(std::string uri, std::string fileUri);

    // 下载失败时，通知图像源更新失败
    void imageDownloadFail(std::string uri);

    // 使用LRU缓存来管理磁盘文件路径与URI的映射
    LRUCache<std::string, bool> remoteImageSourceMap_;

    // 存储图像缓存目录路径
    std::string fileCacheDir_;

private:
    // 存储URI与对应的监听器（支持多个监听器）
    std::unordered_map<std::string, std::vector<std::weak_ptr<ImageSourceUpdateListener>>> m_uriListenersMap;

    // 存储正在下载的图像URI集合
    std::unordered_set<std::string> m_pendingSet;
};

} // namespace svg
} // namespace rnoh
