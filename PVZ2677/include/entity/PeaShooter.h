#ifndef PVZ_PEASHOOTER_H
#define PVZ_PEASHOOTER_H

#include "entity/Plant.h"

class Bullet;

class PeaShooter : public Plant {
public:
    PeaShooter(int row, int col);

    void Update(float dt) override;
    void Render() override;

    bool CanShoot() const;
    void ResetAttackTimer();

private:
    float attackTimer;
};

#endif // PVZ_PEASHOOTER_H
