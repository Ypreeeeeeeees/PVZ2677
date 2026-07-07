#include "scene/SettingsScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"

SettingsScene::SettingsScene() {
    sceneID = SceneID::Settings;
}

void SettingsScene::OnEnter() {
    backButton.Init(40, GameConstants::WINDOW_HEIGHT - 70,
        GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"返回", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);
}

void SettingsScene::OnExit() {
}

void SettingsScene::Update(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();
    backButton.Update(input.GetMouseX(), input.GetMouseY(),
        input.IsMouseDown(), input.IsMouseClicked());

    if (backButton.IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void SettingsScene::Render() {
    cleardevice();
    setbkcolor(RGB(30, 60, 25));
    cleardevice();
    setbkmode(TRANSPARENT);

    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(40, 0, _T("微软雅黑"));
    const wchar_t* title = L"设置";
    outtextxy(40, 30, title);

    setlinecolor(GameConstants::COLOR_TITLE);
    line(40, 80, GameConstants::WINDOW_WIDTH - 40, 80);

    settextcolor(RGB(180, 180, 180));
    settextstyle(24, 0, _T("微软雅黑"));
    const wchar_t* placeholder = L"设置功能将在后续版本中实现...";
    int pw = textwidth(placeholder);
    outtextxy((GameConstants::WINDOW_WIDTH - pw) / 2, 300, placeholder);

    backButton.Render();
}
