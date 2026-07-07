#include "scene/SplashScene.h"
#include <graphics.h>
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"

SplashScene::SplashScene() {
    sceneID = SceneID::Splash;
}

void SplashScene::OnEnter() {
    elapsedTime = 0.0f;
    skipRequested = false;
}

void SplashScene::OnExit() {
}

void SplashScene::Update(float dt) {
    elapsedTime += dt;

    InputManager& input = Game::GetInstance().GetInputManager();
    if (input.IsMouseClicked() || input.IsKeyPressed(VK_SPACE) || input.IsKeyPressed(VK_RETURN)) {
        skipRequested = true;
    }

    if (skipRequested || elapsedTime >= GameConstants::SPLASH_DURATION) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void SplashScene::Render() {
    cleardevice();

    setbkcolor(RGB(0, 0, 0));
    cleardevice();

    setbkmode(TRANSPARENT);

    // 标题
    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(48, 0, _T("微软雅黑"));
    const wchar_t* title = L"植物大战僵尸 Lite";
    int tw = textwidth(title);
    outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 200, title);

    // 副标题
    settextcolor(RGB(200, 200, 200));
    settextstyle(24, 0, _T("微软雅黑"));
    const wchar_t* subtitle = L"程序设计案例实训 - 暑期课程大作业";
    int sw = textwidth(subtitle);
    outtextxy((GameConstants::WINDOW_WIDTH - sw) / 2, 280, subtitle);

    // 提示
    settextcolor(RGB(150, 150, 150));
    settextstyle(18, 0, _T("微软雅黑"));
    const wchar_t* hint = L"点击任意位置或按任意键跳过...";
    int hw = textwidth(hint);
    outtextxy((GameConstants::WINDOW_WIDTH - hw) / 2, 500, hint);

    // 版本信息
    const wchar_t* version = L"v1.0 / EasyX / C++17";
    int vw = textwidth(version);
    outtextxy((GameConstants::WINDOW_WIDTH - vw) / 2, 650, version);
}
