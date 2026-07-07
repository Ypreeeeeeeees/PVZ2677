#ifndef PVZ_SUNFLOWER_H
#define PVZ_SUNFLOWER_H

#include "entity/Plant.h"

class SunFlower : public Plant {
public:
    SunFlower(int row, int col);

    void Update(float dt) override;
    void Render() override;

    bool CanProduceSun() const;
    void ResetSunTimer() { sunTimer = 0.0f; }

private:
    float sunTimer;
};

#endif // PVZ_SUNFLOWER_H
