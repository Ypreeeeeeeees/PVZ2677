#include "scene/DefeatScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"
#include <graphics.h>

DefeatScene::DefeatScene() {
    sceneID = SceneID::Defeat;
}

void DefeatScene::OnEnter() {
    elapsedTime = 0.0f;
}

void DefeatScene::OnExit() {
}

void DefeatScene::Update(float dt) {
    elapsedTime += dt;

    InputManager& input = Game::GetInstance().GetInputManager();
    if (input.IsMouseClicked() || input.IsKeyPressed(VK_SPACE) || input.IsKeyPressed(VK_RETURN)) {
        elapsedTime = GameConstants::SPLASH_DURATION + 1.0f;
    }

    if (elapsedTime >= GameConstants::SPLASH_DURATION + 1.0f) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void DefeatScene::Render() {
    cleardevice();
    setbkcolor(RGB(60, 10, 10));
    cleardevice();

    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 50, 50));
    settextstyle(56, 0, _T("微软雅黑"));
    const wchar_t* title = L"游戏失败";
    int tw = textwidth(title);
    outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 220, title);

    settextcolor(RGB(200, 150, 150));
    settextstyle(22, 0, _T("微软雅黑"));
    const wchar_t* sub = L"僵尸进入了你的房子...";
    int sw = textwidth(sub);
    outtextxy((GameConstants::WINDOW_WIDTH - sw) / 2, 310, sub);

    settextcolor(RGB(150, 150, 150));
    settextstyle(18, 0, _T("微软雅黑"));
    const wchar_t* hint = L"点击或按任意键返回主菜单";
    int hw = textwidth(hint);
    outtextxy((GameConstants::WINDOW_WIDTH - hw) / 2, 500, hint);
}
