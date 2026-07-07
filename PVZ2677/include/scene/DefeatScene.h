#ifndef PVZ_DEFEATSCENE_H
#define PVZ_DEFEATSCENE_H

#include "core/Scene.h"

class DefeatScene : public Scene {
public:
    DefeatScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    float elapsedTime = 0.0f;
};

#endif // PVZ_DEFEATSCENE_H
