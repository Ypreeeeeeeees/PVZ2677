#include "scene/PauseScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"
#include <graphics.h>

PauseScene::PauseScene() {
    sceneID = SceneID::Pause;
}

void PauseScene::OnEnter() {
    continueButton.Init(540, 280, GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"继续游戏", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);

    menuButton.Init(540, 370, GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"返回主菜单", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);
}

void PauseScene::OnExit() {
}

void PauseScene::Update(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();

    continueButton.Update(input.GetMouseX(), input.GetMouseY(),
        input.IsMouseDown(), input.IsMouseClicked());
    menuButton.Update(input.GetMouseX(), input.GetMouseY(),
        input.IsMouseDown(), input.IsMouseClicked());

    if (continueButton.IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Gameplay);
    } else if (menuButton.IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }

    if (input.IsKeyPressed(VK_ESCAPE)) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Gameplay);
    }
}

void PauseScene::Render() {
    // 半透明遮罩
    setfillcolor(RGB(80, 80, 80));
    solidrectangle(0, 0, GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);

    setbkmode(TRANSPARENT);
    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(48, 0, _T("微软雅黑"));
    const wchar_t* title = L"暂停";
    int tw = textwidth(title);
    outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 140, title);

    continueButton.Render();
    menuButton.Render();
}
