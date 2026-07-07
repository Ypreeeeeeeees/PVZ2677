#include "scene/VictoryScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"
#include <graphics.h>

VictoryScene::VictoryScene() {
    sceneID = SceneID::Victory;
}

void VictoryScene::OnEnter() {
    elapsedTime = 0.0f;
}

void VictoryScene::OnExit() {
}

void VictoryScene::Update(float dt) {
    elapsedTime += dt;

    InputManager& input = Game::GetInstance().GetInputManager();
    if (input.IsMouseClicked() || input.IsKeyPressed(VK_SPACE) || input.IsKeyPressed(VK_RETURN)) {
        elapsedTime = GameConstants::SPLASH_DURATION + 1.0f;
    }

    if (elapsedTime >= GameConstants::SPLASH_DURATION + 1.0f) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void VictoryScene::Render() {
    cleardevice();
    setbkcolor(RGB(10, 50, 10));
    cleardevice();

    setbkmode(TRANSPARENT);
    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(56, 0, _T("微软雅黑"));
    const wchar_t* title = L"胜利！";
    int tw = textwidth(title);
    outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 220, title);

    settextcolor(RGB(150, 200, 150));
    settextstyle(22, 0, _T("微软雅黑"));
    const wchar_t* sub = L"所有僵尸已被消灭！";
    int sw = textwidth(sub);
    outtextxy((GameConstants::WINDOW_WIDTH - sw) / 2, 310, sub);

    settextcolor(RGB(150, 150, 150));
    settextstyle(18, 0, _T("微软雅黑"));
    const wchar_t* hint = L"点击或按任意键返回主菜单";
    int hw = textwidth(hint);
    outtextxy((GameConstants::WINDOW_WIDTH - hw) / 2, 500, hint);
}
