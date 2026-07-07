#include "system/ResourceManager.h"

ResourceManager::~ResourceManager() {
    Clear();
}

IMAGE* ResourceManager::LoadImage(const std::wstring& key, const std::wstring& filePath) {
    if (imageCache.find(key) != imageCache.end()) {
        return imageCache[key];
    }

    IMAGE* img = new IMAGE();
    loadimage(img, filePath.c_str());
    imageCache[key] = img;
    return img;
}

IMAGE* ResourceManager::GetImage(const std::wstring& key) {
    auto it = imageCache.find(key);
    if (it != imageCache.end()) {
        return it->second;
    }
    return nullptr;
}

bool ResourceManager::IsLoaded(const std::wstring& key) const {
    return imageCache.find(key) != imageCache.end();
}

void ResourceManager::Clear() {
    for (auto& pair : imageCache) {
        delete pair.second;
    }
    imageCache.clear();
}
