#include "system/CollisionManager.h"
#include "entity/Bullet.h"
#include "entity/Plant.h"
#include "entity/Zombie.h"
#include "system/Map.h"
#include "utils/Constants.h"

void CollisionManager::CheckBulletZombie(
    std::vector<std::unique_ptr<Bullet>>& bullets,
    std::vector<std::unique_ptr<Zombie>>& zombies) {

    for (auto& bullet : bullets) {
        if (!bullet->IsAlive()) continue;
        for (auto& zombie : zombies) {
            if (!zombie->IsAlive()) continue;
            if (bullet->GetRow() != zombie->GetRow()) continue;

            int cellW = GameConstants::CELL_SIZE * 2 / 3;
            int cellH = cellW;

            if (RectCircleCollide(zombie->GetX(), zombie->GetY(),
                                  static_cast<float>(cellW), static_cast<float>(cellH),
                                  bullet->GetX(), bullet->GetY(), bullet->GetRadius())) {
                zombie->TakeDamage(bullet->GetDamage());
                bullet->Destroy();
                break;
            }
        }
    }
}

void CollisionManager::CheckZombiePlant(
    std::vector<std::unique_ptr<Zombie>>& zombies, Map& map) {

    int cellW = GameConstants::CELL_SIZE * 2 / 3;
    int cellH = cellW;

    for (auto& zombie : zombies) {
        if (!zombie->IsAlive() || zombie->GetState() == ZombieState::Dead) continue;
        int row = zombie->GetRow();
        bool foundPlant = false;

        for (int c = 0; c < GameConstants::MAP_COLS; c++) {
            Plant* plant = map.GetPlant(row, c);
            if (!plant || !plant->IsAlive()) continue;

            Point pt = map.CellToScreen(row, c);
            float plantLeft = static_cast<float>(pt.x - cellW / 2);
            float plantRight = static_cast<float>(pt.x + cellW / 2);
            float zombieX = zombie->GetX();

            if (zombieX <= plantRight && zombieX >= plantLeft - 10.0f) {
                zombie->SetTargetPlantAlive(true);
                foundPlant = true;
                break;
            }
        }

        if (!foundPlant) {
            zombie->SetTargetPlantAlive(false);
        }
    }
}

bool CollisionManager::CheckZombieHouse(
    std::vector<std::unique_ptr<Zombie>>& zombies, int houseBoundaryX) {

    for (auto& zombie : zombies) {
        if (!zombie->IsAlive()) continue;
        if (zombie->GetX() <= static_cast<float>(houseBoundaryX)) {
            return true;
        }
    }
    return false;
}

bool CollisionManager::RectCircleCollide(
    float rx, float ry, float rw, float rh,
    float cx, float cy, float cr) {

    float closestX = (cx < rx) ? rx : (cx > rx + rw) ? rx + rw : cx;
    float closestY = (cy < ry) ? ry : (cy > ry + rh) ? ry + rh : cy;

    float dx = cx - closestX;
    float dy = cy - closestY;
    return (dx * dx + dy * dy) <= (cr * cr);
}

bool CollisionManager::RectRectCollide(
    float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {

    return !(x1 + w1 < x2 || x2 + w2 < x1 ||
             y1 + h1 < y2 || y2 + h2 < y1);
}
