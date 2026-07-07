#ifndef PVZ_NORMALZOMBIE_H
#define PVZ_NORMALZOMBIE_H

#include "entity/Zombie.h"

class NormalZombie : public Zombie {
public:
    NormalZombie(int row, float x, float y);

    void Update(float dt) override;
    void Render() override;
};

#endif // PVZ_NORMALZOMBIE_H
