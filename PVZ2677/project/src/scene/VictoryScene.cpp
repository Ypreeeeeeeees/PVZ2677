#include "scene/VictoryScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"
#include <graphics.h>
#include <string>

VictoryScene::VictoryScene() {
    sceneID = SceneID::Victory;
}

void VictoryScene::OnEnter() {
    elapsedTime = 0.0f;

    // 从 Game 单例读取通关信息
    auto diff = Game::GetInstance().GetDifficulty();
    const wchar_t* diffNames[] = { L"简单", L"困难", L"地狱" };
    int mowers = Game::GetInstance().GetRemainingMowers();

    line1 = L"恭喜! 你通关了" + std::wstring(diffNames[static_cast<int>(diff)]) + L"模式";
    line2 = L"并保留了 " + std::to_wstring(mowers) + L" 个小推车!";
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

    // 第1行
    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(46, 0, _T("微软雅黑"));
    int tw = textwidth(line1.c_str());
    outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 220, line1.c_str());

    // 第2行
    settextcolor(RGB(150, 200, 150));
    settextstyle(36, 0, _T("微软雅黑"));
    int sw = textwidth(line2.c_str());
    outtextxy((GameConstants::WINDOW_WIDTH - sw) / 2, 310, line2.c_str());

    // 提示
    settextcolor(RGB(150, 150, 150));
    settextstyle(18, 0, _T("微软雅黑"));
    const wchar_t* hint = L"点击或按任意键返回主菜单";
    int hw = textwidth(hint);
    outtextxy((GameConstants::WINDOW_WIDTH - hw) / 2, 500, hint);
}
