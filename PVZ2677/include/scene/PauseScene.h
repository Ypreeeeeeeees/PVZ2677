#ifndef PVZ_PAUSESCENE_H
#define PVZ_PAUSESCENE_H

#include "core/Scene.h"
#include "component/Button.h"

class PauseScene : public Scene {
public:
    PauseScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    Button continueButton;
    Button menuButton;
};

#endif // PVZ_PAUSESCENE_H
