#ifndef PVZ_COLLISIONMANAGER_H
#define PVZ_COLLISIONMANAGER_H

#include <vector>
#include <memory>

class Bullet;
class Zombie;
class Map;

class CollisionManager {
public:
    CollisionManager() = default;

    void CheckBulletZombie(std::vector<std::unique_ptr<Bullet>>& bullets,
                           std::vector<std::unique_ptr<Zombie>>& zombies);

    void CheckZombiePlant(std::vector<std::unique_ptr<Zombie>>& zombies,
                          Map& map);

    bool CheckZombieHouse(std::vector<std::unique_ptr<Zombie>>& zombies,
                          int houseBoundaryX);

private:
    bool RectCircleCollide(float rx, float ry, float rw, float rh,
                           float cx, float cy, float cr);
    bool RectRectCollide(float x1, float y1, float w1, float h1,
                         float x2, float y2, float w2, float h2);
};

#endif // PVZ_COLLISIONMANAGER_H
