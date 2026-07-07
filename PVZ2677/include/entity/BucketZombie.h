#ifndef PVZ_BUCKETZOMBIE_H
#define PVZ_BUCKETZOMBIE_H

#include "entity/Zombie.h"

class BucketZombie : public Zombie {
public:
    BucketZombie(int row, float x, float y);

    void Update(float dt) override;
    void Render() override;
};

#endif // PVZ_BUCKETZOMBIE_H
