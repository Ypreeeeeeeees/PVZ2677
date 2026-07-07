#include "scene/AboutScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"

AboutScene::AboutScene() {
    sceneID = SceneID::About;
}

void AboutScene::OnEnter() {
    backButton.Init(40, GameConstants::WINDOW_HEIGHT - 70,
        GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"返回", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);
}

void AboutScene::OnExit() {
}

void AboutScene::Update(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();
    backButton.Update(input.GetMouseX(), input.GetMouseY(),
        input.IsMouseDown(), input.IsMouseClicked());

    if (backButton.IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void AboutScene::Render() {
    cleardevice();
    setbkcolor(RGB(30, 60, 25));
    cleardevice();
    setbkmode(TRANSPARENT);

    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(40, 0, _T("微软雅黑"));
    const wchar_t* title = L"关于作者";
    outtextxy(40, 30, title);

    setlinecolor(GameConstants::COLOR_TITLE);
    line(40, 80, GameConstants::WINDOW_WIDTH - 40, 80);

    settextcolor(RGB(220, 220, 220));
    settextstyle(24, 0, _T("微软雅黑"));

    int y = 140;
    int lineHeight = 45;

    const wchar_t* info[] = {
        L"课程名称：程序设计案例实训",
        L"项目名称：植物大战僵尸 Lite (PVZ Lite)",
        L"开发人员：",
        L"袁鹏 250809010305",
        L"技术栈：C++17 + EasyX + Visual Studio 2022",
        L"开发环境：Windows 10 / MSVC v143",
        L"开发日期：2026 年 7 月",
        L"",
        L"感谢 EasyX 图形库提供技术支持！",
        L"本作品仅用于课程学习目的。",
    };

    for (auto& line : info) {
        outtextxy(60, y, line);
        y += lineHeight;
    }

    backButton.Render();
}
