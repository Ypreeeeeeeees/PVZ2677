#include "component/HUD.h"
#include "utils/Constants.h"
#include <graphics.h>
#include <string>

HUD::HUD()
    : sunCount(GameConstants::INITIAL_SUN), currentWave(0), totalWaves(0) {
}

bool HUD::SpendSun(int amount) {
    if (sunCount < amount) return false;
    sunCount -= amount;
    return true;
}

void HUD::Render() {
    int x = 10;
    int y = 10;

    // 阳光图标（黄色圆形占位）
    setfillcolor(RGB(255, 230, 50));
    solidcircle(x + 20, y + 20, 18);
    setfillcolor(RGB(255, 255, 150));
    solidcircle(x + 20, y + 20, 10);

    // 数值
    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 255, 200));
    settextstyle(26, 0, _T("微软雅黑"));

    std::wstring text = std::to_wstring(sunCount);
    outtextxy(x + 48, y + 6, text.c_str());

    // 波次信息
    if (totalWaves > 0) {
        settextcolor(RGB(220, 180, 100));
        settextstyle(24, 0, _T("微软雅黑"));
        int waveX = GameConstants::WINDOW_WIDTH - 220;
        std::wstring waveText = L"波次 " + std::to_wstring(currentWave)
                              + L" / " + std::to_wstring(totalWaves);
        outtextxy(waveX, 8, waveText.c_str());
    }
}
