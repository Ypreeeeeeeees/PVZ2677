#include "entity/LawnMower.h"
#include "utils/Constants.h"
#include <graphics.h>

LawnMower::LawnMower(int row, float x, float y, float speed)
    : row(row), x(x), y(y), speed(speed),
      state(LawnMowerState::Idle), travelDistance(0.0f) {
}

void LawnMower::Update(float dt) {
    if (state != LawnMowerState::Moving) return;

    x += speed * dt;
    travelDistance += speed * dt;

    if (x > GameConstants::WINDOW_WIDTH + 50) {
        state = LawnMowerState::Gone;
    }
}

void LawnMower::Render() {
    if (state == LawnMowerState::Gone) return;

    int drawX = static_cast<int>(x);
    int drawY = static_cast<int>(y);
    int w = 50;
    int h = 30;

    // 车身（灰色）
    setfillcolor(state == LawnMowerState::Moving ? RGB(200, 180, 140) : RGB(140, 120, 90));
    solidroundrect(drawX, drawY, drawX + w, drawY + h, 4, 4);

    // 轮子
    setfillcolor(RGB(60, 60, 60));
    solidcircle(drawX + 10, drawY + h, 8);
    solidcircle(drawX + w - 10, drawY + h, 8);
}

void LawnMower::Trigger() {
    if (state == LawnMowerState::Idle) {
        state = LawnMowerState::Moving;
    }
}
