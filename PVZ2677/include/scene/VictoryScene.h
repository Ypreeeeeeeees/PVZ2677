#ifndef PVZ_VICTORYSCENE_H
#define PVZ_VICTORYSCENE_H

#include "core/Scene.h"

class VictoryScene : public Scene {
public:
    VictoryScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    float elapsedTime = 0.0f;
};

#endif // PVZ_VICTORYSCENE_H
