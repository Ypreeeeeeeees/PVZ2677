#ifndef PVZ_CONFIG_H
#define PVZ_CONFIG_H

#include <string>

class Config {
public:
    Config();

    void SetWindowTitle(const std::wstring& title) { windowTitle = title; }
    const std::wstring& GetWindowTitle() const { return windowTitle; }

    void SetVolumeBGM(int vol) { volumeBGM = vol; }
    int GetVolumeBGM() const { return volumeBGM; }

    void SetVolumeSFX(int vol) { volumeSFX = vol; }
    int GetVolumeSFX() const { return volumeSFX; }

    bool IsFullscreen() const { return fullscreen; }
    void SetFullscreen(bool fs) { fullscreen = fs; }

private:
    std::wstring windowTitle;
    int volumeBGM;
    int volumeSFX;
    bool fullscreen;
};

#endif // PVZ_CONFIG_H
