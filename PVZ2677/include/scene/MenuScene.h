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
    bool skipInputFrame;     // 首帧跳过输入，防止跨场景误触
};

#endif // PVZ_MENUSCENE_H
