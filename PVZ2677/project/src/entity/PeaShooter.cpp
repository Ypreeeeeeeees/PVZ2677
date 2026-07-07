#include "entity/PeaShooter.h"
#include "utils/Constants.h"
#include <graphics.h>

PeaShooter::PeaShooter(int row, int col)
    : Plant(L"豌豆射手", row, col,
            GameConstants::PEASHOOTER_HEALTH,
            GameConstants::PEASHOOTER_HEALTH,
            GameConstants::PEASHOOTER_PRICE,
            GameConstants::PEASHOOTER_COOLDOWN,
            GameConstants::PEASHOOTER_ATTACK_INTERVAL),
      attackTimer(0.0f) {
}

void PeaShooter::Update(float dt) {
    Plant::Update(dt);

    if (!isAlive) return;
    if (state == PlantState::Planting || state == PlantState::Dead) return;

    attackTimer += dt;
}

void PeaShooter::Render() {
    if (state == PlantState::Attacking) {
        // 攻击时偏移绘制以模拟"头部伸长"效果（占位）
    }
    Plant::Render();
}

bool PeaShooter::CanShoot() const {
    return isAlive && state != PlantState::Planting &&
           state != PlantState::Dead &&
           attackTimer >= attackSpeed;
}

void PeaShooter::ResetAttackTimer() {
    attackTimer = 0.0f;
}
