#ifndef PVZ_RESOURCEMANAGER_H
#define PVZ_RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <graphics.h>

#define RES_BASE        L"./assets/"
#define RES_IMAGE       L"./assets/images/"
#define RES_PLANT       L"./assets/images/plants/"
#define RES_ZOMBIE      L"./assets/images/zombies/"
#define RES_BULLET      L"./assets/images/bullets/"
#define RES_UI          L"./assets/images/ui/"
#define RES_BG          L"./assets/images/backgrounds/"
#define RES_SOUND       L"./assets/sounds/"
#define RES_FONT        L"./assets/fonts/"

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    IMAGE* LoadImage(const std::wstring& key, const std::wstring& filePath);
    IMAGE* GetImage(const std::wstring& key);

    bool IsLoaded(const std::wstring& key) const;
    void Clear();

private:
    std::unordered_map<std::wstring, IMAGE*> imageCache;
};

#endif // PVZ_RESOURCEMANAGER_H
