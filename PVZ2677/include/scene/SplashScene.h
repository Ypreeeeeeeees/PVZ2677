#ifndef PVZ_SPLASHSCENE_H
#define PVZ_SPLASHSCENE_H

#include "core/Scene.h"

class SplashScene : public Scene {
public:
    SplashScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    float elapsedTime = 0.0f;
    bool skipRequested = false;
};

#endif // PVZ_SPLASHSCENE_H
