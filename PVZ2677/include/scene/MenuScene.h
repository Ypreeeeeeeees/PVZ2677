#ifndef PVZ_MENUSCENE_H
#define PVZ_MENUSCENE_H

#include "core/Scene.h"
#include "component/Button.h"

class MenuScene : public Scene {
public:
    MenuScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    enum { BTN_START, BTN_HELP, BTN_SETTINGS, BTN_ABOUT, BTN_EXIT, BTN_COUNT };
    Button buttons[BTN_COUNT];
};

#endif // PVZ_MENUSCENE_H
