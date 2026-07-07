#include "entity/NormalZombie.h"
#include "utils/Constants.h"
#include <graphics.h>

NormalZombie::NormalZombie(int row, float x, float y)
    : Zombie(L"普通僵尸", row, x, y,
             GameConstants::NORMAL_ZOMBIE_HEALTH,
             GameConstants::NORMAL_ZOMBIE_HEALTH,
             GameConstants::NORMAL_ZOMBIE_SPEED,
             GameConstants::NORMAL_ZOMBIE_ATTACK,
             1.0f) {
}

void NormalZombie::Update(float dt) {
    Zombie::Update(dt);
}

void NormalZombie::Render() {
    Zombie::Render();
}
