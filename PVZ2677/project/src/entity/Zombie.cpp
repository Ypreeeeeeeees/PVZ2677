#include "entity/Zombie.h"
#include "utils/Constants.h"
#include <graphics.h>

Zombie::Zombie(const std::wstring& name, int row, float x, float y,
               int health, int maxHealth, float speed, int attackPower,
               float attackInterval)
    : name(name), row(row), x(x), y(y),
      health(health), maxHealth(maxHealth), speed(speed),
      attackPower(attackPower), attackInterval(attackInterval),
      attackTimer(0.0f), isAlive(true), reachedEnd(false),
      targetPlantAlive(false), state(ZombieState::Walking),
      deathTimer(0.0f) {
}

void Zombie::Update(float dt) {
    if (!isAlive) return;

    switch (state) {
    case ZombieState::Walking:
        x -= speed * dt;
        if (!targetPlantAlive && health > 0) {
            state = ZombieState::Walking;
        }
        break;

    case ZombieState::Attacking:
        attackTimer += dt;
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;
        }
        if (!targetPlantAlive) {
            state = ZombieState::Walking;
            attackTimer = 0.0f;
        }
        break;

    case ZombieState::Dead:
        deathTimer += dt;
        if (deathTimer >= 0.8f) {
            isAlive = false;
        }
        break;
    }
}

void Zombie::Render() {
    if (!isAlive) return;

    int w = GameConstants::CELL_SIZE * 2 / 3;
    int h = GameConstants::CELL_SIZE * 2 / 3;
    int drawX = static_cast<int>(x);
    int drawY = static_cast<int>(y);

    switch (state) {
    case ZombieState::Walking:
        // 灰色矩形 + 水平偏移模拟行走摇摆
        setfillcolor(RGB(130, 130, 130));
        solidroundrect(drawX, drawY, drawX + w, drawY + h, 4, 4);
        // "眼睛"
        setfillcolor(RGB(255, 50, 50));
        solidcircle(drawX + w * 3 / 4, drawY + h / 4, 4);
        solidcircle(drawX + w * 3 / 4, drawY + h * 2 / 3, 4);
        break;

    case ZombieState::Attacking: {
        // 暗红色矩形 + 攻击动画偏移
        setfillcolor(RGB(180, 80, 80));
        int offsetX = static_cast<int>(attackTimer * 10.0f) % 6 - 3;
        solidroundrect(drawX + offsetX, drawY, drawX + w + offsetX, drawY + h, 4, 4);
        setfillcolor(RGB(255, 30, 30));
        solidcircle(drawX + offsetX + w * 3 / 4, drawY + h / 4, 4);
        solidcircle(drawX + offsetX + w * 3 / 4, drawY + h * 2 / 3, 4);
        break;
    }

    case ZombieState::Dead:
        // 渐隐效果（占位：深色矩形）
        setfillcolor(RGB(60, 60, 60));
        solidroundrect(drawX, drawY + h / 3, drawX + w, drawY + h, 4, 4);
        break;
    }
}

void Zombie::TakeDamage(int damage) {
    if (!isAlive) return;
    health -= damage;
    if (health <= 0) {
        health = 0;
        state = ZombieState::Dead;
        deathTimer = 0.0f;
    }
}
