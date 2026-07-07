#include "entity/Plant.h"
#include "utils/Constants.h"
#include <graphics.h>

Plant::Plant(const std::wstring& name, int row, int col,
             int health, int maxHealth, int price, float cooldown,
             float attackSpeed)
    : name(name), row(row), col(col),
      health(health), maxHealth(maxHealth), price(price),
      cooldown(cooldown), attackSpeed(attackSpeed),
      isAlive(true), state(PlantState::Planting),
      plantTimer(0.0f), deathTimer(0.0f) {
}

void Plant::Update(float dt) {
    if (!isAlive) return;

    switch (state) {
    case PlantState::Planting:
        plantTimer += dt;
        if (plantTimer >= 0.5f) {
            state = PlantState::Idle;
        }
        break;

    case PlantState::Idle:
    case PlantState::Attacking:
        // 子类实现具体逻辑
        break;

    case PlantState::Dead:
        deathTimer += dt;
        // 死亡动画 1 秒后标记完全死亡
        if (deathTimer >= 1.0f) {
            isAlive = false;
        }
        break;
    }
}

void Plant::Render() {
    if (!isAlive) return;

    int screenX = 0, screenY = 0;
    // 坐标转换由 GameplayScene 在调用 Render 前设置，此处用占位矩形

    switch (state) {
    case PlantState::Planting: {
        // 种植动画：半透明缩放入场（占位：浅绿色矩形）
        float scale = plantTimer / 0.5f;
        int size = static_cast<int>(GameConstants::CELL_SIZE * scale * 0.6f);
        int cx = screenX + GameConstants::CELL_SIZE / 2;
        int cy = screenY + GameConstants::CELL_SIZE / 2;
        setfillcolor(RGB(100, 200, 100));
        solidrectangle(cx - size / 2, cy - size / 2, cx + size / 2, cy + size / 2);
        break;
    }
    case PlantState::Idle: {
        setfillcolor(RGB(80, 180, 80));
        int s = GameConstants::CELL_SIZE * 2 / 3;
        solidroundrect(screenX + 18, screenY + 18,
                       screenX + 18 + s, screenY + 18 + s, 5, 5);
        break;
    }
    case PlantState::Attacking: {
        setfillcolor(RGB(60, 200, 60));
        int s = GameConstants::CELL_SIZE * 2 / 3;
        solidroundrect(screenX + 18, screenY + 18,
                       screenX + 18 + s, screenY + 18 + s, 5, 5);
        break;
    }
    case PlantState::Dead:
        // 死亡动画由子类处理，此处不渲染
        break;
    }
}

void Plant::TakeDamage(int damage) {
    if (!isAlive) return;
    if (state == PlantState::Dead) return;  // 已死，不再受伤
    health -= damage;
    if (health <= 0) {
        health = 0;
        state = PlantState::Dead;
        deathTimer = 0.0f;
    }
}
