#include "entity/Sun.h"
#include "utils/Constants.h"
#include <graphics.h>

Sun::Sun(float x, float y, int value)
    : x(x), y(y), targetY(y), value(value),
      state(SunState::Spawning), isFalling(false),
      timer(0.0f), spawnTimer(0.0f), vanishTimer(0.0f) {
}

void Sun::Update(float dt) {
    switch (state) {
    case SunState::Spawning:
        spawnTimer += dt;
        // 缩放入场动画 0.3 秒
        if (spawnTimer >= 0.3f) {
            state = SunState::Floating;
        }
        break;

    case SunState::Floating:
        timer += dt;
        if (isFalling) {
            // 自然阳光：匀速飘落
            y += 30.0f * dt;
            if (y >= targetY) {
                y = targetY;
                isFalling = false;
            }
        }
        // 8 秒超时消失
        if (timer >= GameConstants::SUN_LIFETIME) {
            state = SunState::Vanished;
        }
        break;

    case SunState::Collected:
        // 飞向 HUD（由 GameplayScene 处理飞行逻辑）
        vanishTimer += dt;
        if (vanishTimer >= 0.5f) {
            state = SunState::Vanished;
        }
        break;

    case SunState::Vanished:
        break;
    }
}

void Sun::Render() {
    if (state == SunState::Vanished) return;

    int drawX = static_cast<int>(x);
    int drawY = static_cast<int>(y);
    int radius = 20;

    float scale = 1.0f;
    if (state == SunState::Spawning) {
        scale = spawnTimer / 0.3f;
    }

    int r = static_cast<int>(radius * scale);

    // 阳光占位：金黄色圆形 + 光晕
    setfillcolor(RGB(255, 230, 50));
    solidcircle(drawX, drawY, r);

    setfillcolor(RGB(255, 255, 150));
    solidcircle(drawX, drawY, r * 2 / 3);
}

void Sun::Collect() {
    if (state == SunState::Floating) {
        state = SunState::Collected;
        vanishTimer = 0.0f;
    }
}
