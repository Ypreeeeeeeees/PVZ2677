#ifndef PVZ_ABOUTSCENE_H
#define PVZ_ABOUTSCENE_H

#include "core/Scene.h"
#include "component/Button.h"

class AboutScene : public Scene {
public:
    AboutScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    Button backButton;
};

#endif // PVZ_ABOUTSCENE_H
