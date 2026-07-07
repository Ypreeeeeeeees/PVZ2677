#include "entity/BucketZombie.h"
#include "utils/Constants.h"
#include <graphics.h>

BucketZombie::BucketZombie(int row, float x, float y)
    : Zombie(L"铁桶僵尸", row, x, y,
             GameConstants::BUCKET_ZOMBIE_HEALTH,
             GameConstants::BUCKET_ZOMBIE_HEALTH,
             GameConstants::BUCKET_ZOMBIE_SPEED,
             GameConstants::NORMAL_ZOMBIE_ATTACK,
             1.0f) {
}

void BucketZombie::Update(float dt) {
    Zombie::Update(dt);
}

void BucketZombie::Render() {
    Zombie::Render();

    if (!isAlive) return;

    int w = GameConstants::CELL_SIZE * 2 / 3;
    int drawX = static_cast<int>(x);
    int drawY = static_cast<int>(y);

    // 铁桶占位：头顶深灰色矩形
    setfillcolor(RGB(80, 80, 90));
    solidrectangle(drawX + 5, drawY - 12, drawX + w - 5, drawY);
}
