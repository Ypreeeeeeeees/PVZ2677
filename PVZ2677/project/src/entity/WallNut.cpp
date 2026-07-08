#include "entity/WallNut.h"
#include "utils/Constants.h"
#include <graphics.h>

WallNut::WallNut(int row, int col)
    : Plant(L"坚果墙", row, col,
            GameConstants::WALLNUT_HEALTH,
            GameConstants::WALLNUT_HEALTH,
            GameConstants::WALLNUT_PRICE,
            GameConstants::WALLNUT_COOLDOWN,
            0.0f) {                            // 不攻击
}

void WallNut::Update(float dt) {
    Plant::Update(dt);
}

void WallNut::Render() {
    if (!isAlive) return;

    // 坚果墙占位：棕色圆角矩形
    setfillcolor(RGB(160, 120, 70));
    int s = GameConstants::CELL_SIZE * 2 / 3;
    solidroundrect(0, 0, s, s, 8, 8);

    // 表情：两个小圆点
    setfillcolor(RGB(60, 40, 20));
    solidcircle(s / 3, s / 3, 3);
    solidcircle(s * 2 / 3, s / 3, 3);
    solidcircle(s / 2, s * 2 / 3, 3);

    // 血条
    if (health < maxHealth) {
        int barW = s;
        int barH = 6;
        int barX = 0;
        int barY = -10;
        float ratio = static_cast<float>(health) / static_cast<float>(maxHealth);
        int fillW = static_cast<int>(barW * ratio);

        setfillcolor(RGB(60, 60, 60));
        solidrectangle(barX, barY, barX + barW, barY + barH);
        COLORREF hpColor = (ratio > 0.5f) ? RGB(100, 220, 80)
                         : (ratio > 0.25f) ? RGB(220, 200, 50)
                         : RGB(220, 60, 60);
        setfillcolor(hpColor);
        solidrectangle(barX, barY, barX + fillW, barY + barH);
    }
}
