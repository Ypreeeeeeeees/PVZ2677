#ifndef PVZ_HELPSCENE_H
#define PVZ_HELPSCENE_H

#include "core/Scene.h"
#include "component/Button.h"

class HelpScene : public Scene {
public:
    HelpScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    Button backButton;
};

#endif // PVZ_HELPSCENE_H
