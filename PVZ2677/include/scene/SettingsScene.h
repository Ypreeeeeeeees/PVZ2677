#ifndef PVZ_SETTINGSSCENE_H
#define PVZ_SETTINGSSCENE_H

#include "core/Scene.h"
#include "component/Button.h"

class SettingsScene : public Scene {
public:
    SettingsScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    Button backButton;
};

#endif // PVZ_SETTINGSSCENE_H
