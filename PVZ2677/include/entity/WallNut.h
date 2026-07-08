#ifndef PVZ_WALLNUT_H
#define PVZ_WALLNUT_H

#include "entity/Plant.h"

class WallNut : public Plant {
public:
    WallNut(int row, int col);

    void Update(float dt) override;
    void Render() override;
};

#endif // PVZ_WALLNUT_H
