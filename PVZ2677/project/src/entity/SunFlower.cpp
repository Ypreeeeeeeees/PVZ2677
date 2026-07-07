#include "entity/SunFlower.h"
#include "utils/Constants.h"
#include <graphics.h>

SunFlower::SunFlower(int row, int col)
    : Plant(L"向日葵", row, col,
            GameConstants::SUNFLOWER_HEALTH,
            GameConstants::SUNFLOWER_HEALTH,
            GameConstants::SUNFLOWER_PRICE,
            GameConstants::SUNFLOWER_COOLDOWN,
            0.0f),                            // attackSpeed = 0
      sunTimer(0.0f) {
}

void SunFlower::Update(float dt) {
    Plant::Update(dt);

    if (!isAlive) return;
    if (state == PlantState::Planting || state == PlantState::Dead) return;

    sunTimer += dt;
}

void SunFlower::Render() {
    Plant::Render();
}

bool SunFlower::CanProduceSun() const {
    return isAlive && state != PlantState::Planting &&
           state != PlantState::Dead &&
           sunTimer >= GameConstants::SUNFLOWER_PRODUCE_INTERVAL;
}

// 在外部调用 ResetSunTimer 后重置（由 GameplayScene 调用）
