/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGImageModule.h"
#include "utils/StringUtils.h"

using namespace facebook;

namespace rnoh {
namespace svg {
RNSVGImageModule::RNSVGImageModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    methodMap_ = {
        ARK_ASYNC_METHOD_METADATA(getCacheDir, 0),
    };

    // 获取缓存路径前缀
    auto cache = this->callSync("getCacheDir", {});
    m_fileCacheDir = cache.asString() + "/";
    
    // 确保缓存目录存在
    try {
        fs::path cachePath(m_fileCacheDir);
        if (!fs::exists(cachePath)) {
            if (auto result = fs::create_directories(cachePath)) {
                LOG(INFO) << "[SVGImage] Created cache directory: " << m_fileCacheDir;
            } else {
                LOG(WARNING) << "[SVGImage] Failed to create cache directory: " << m_fileCacheDir;
            }
        } else if (!fs::is_directory(cachePath)) {
            LOG(ERROR) << "[SVGImage] Cache path exists but is not a directory: " << m_fileCacheDir;
            // 尝试创建备份目录
            std::string backupDir = m_fileCacheDir + "_backup";
            fs::create_directories(backupDir);
            m_fileCacheDir = backupDir + "/";
            LOG(INFO) << "[SVGImage] Using backup cache directory: " << m_fileCacheDir;
        }
    } catch (const std::exception& e) {
        LOG(ERROR) << "[SVGImage] Error creating/validating cache directory: " << e.what();
        // 使用临时目录作为后备方案
        m_fileCacheDir = "/data/local/tmp/rnsvg_cache/";
        try {
            fs::create_directories(m_fileCacheDir);
        } catch (...) {
            LOG(ERROR) << "[SVGImage] Failed to create temp cache directory";
        }
    }
    
    m_imageSourceResolver = std::make_shared<ImageSourceResolver>(m_fileCacheDir);

    fs::path directoryPath = m_fileCacheDir;
    // 将已有的缓存文件名放入remoteImageSourceMap
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
        for (const auto &entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.path())) {
                m_imageSourceResolver->remoteImageSourceMap_.put(entry.path().filename(), true);
            }
        }
    }
}

/**
 *
 * @param uri 图片uri
 * @param headers 请求头
 */
void RNSVGImageModule::downloadImage(const std::string &uri, const std::map<std::string, std::string> &headers) {
    HttpTaskProcessor *processor = new HttpTaskProcessor();
    processor->instance_ = m_imageSourceResolver;
    processor->filePath_ = m_fileCacheDir + StringUtils::generateHashedFileName(uri);

    if (headers.empty()) {
        processor->launchHttpRequest(uri.c_str());
    } else {
        processor->launchHttpRequestWithHeaders(uri.c_str(), headers);
    }
}

} // namespace svg
} // namespace rnoh
