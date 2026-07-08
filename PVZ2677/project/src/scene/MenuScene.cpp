#include "scene/MenuScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"

MenuScene::MenuScene() {
    sceneID = SceneID::Menu;
    skipInputFrame = false;
    difficultyIndex = 0;
}

void MenuScene::OnEnter() {
    skipInputFrame = true;
    difficultyIndex = static_cast<int>(Game::GetInstance().GetDifficulty());

    int buttonWidth = GameConstants::BUTTON_WIDTH;
    int buttonHeight = GameConstants::BUTTON_HEIGHT;
    int centerX = (GameConstants::WINDOW_WIDTH - buttonWidth) / 2;
    int startY = 280;
    int gap = 80;

    buttons[BTN_START].Init(centerX, startY, buttonWidth, buttonHeight,
        L"开始游戏", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);

    buttons[BTN_HELP].Init(centerX, startY + gap, buttonWidth, buttonHeight,
        L"游戏说明", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);

    buttons[BTN_SETTINGS].Init(centerX, startY + gap * 2, buttonWidth, buttonHeight,
        L"难度: 简单", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);

    buttons[BTN_ABOUT].Init(centerX, startY + gap * 3, buttonWidth, buttonHeight,
        L"关于作者", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);

    buttons[BTN_EXIT].Init(centerX, startY + gap * 4, buttonWidth, buttonHeight,
        L"退出游戏", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);
}

void MenuScene::OnExit() {
}

void MenuScene::Update(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();

    if (skipInputFrame) {
        skipInputFrame = false;
        return;
    }

    int mx = input.GetMouseX();
    int my = input.GetMouseY();

    for (int i = 0; i < BTN_COUNT; i++) {
        buttons[i].Update(mx, my, input.IsMouseDown(), input.IsMouseClicked());
    }

    if (buttons[BTN_START].IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Gameplay);
    } else if (buttons[BTN_HELP].IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Help);
    } else if (buttons[BTN_SETTINGS].IsClicked()) {
        difficultyIndex = (difficultyIndex + 1) % 3;
        Game::GetInstance().SetDifficulty(static_cast<Difficulty>(difficultyIndex));
    } else if (buttons[BTN_ABOUT].IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::About);
    } else if (buttons[BTN_EXIT].IsClicked()) {
        Game::GetInstance().Quit();
    }
}

void MenuScene::Render() {
    cleardevice();

    setbkcolor(RGB(45, 90, 39));
    cleardevice();

    setbkmode(TRANSPARENT);

    // 标题
    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(60, 0, _T("微软雅黑"));
    const wchar_t* title = L"植物大战僵尸 Lite";
    int tw = textwidth(title);
    outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 120, title);

    // 装饰线
    setlinecolor(GameConstants::COLOR_TITLE);
    setlinestyle(PS_SOLID, 2);
    int lineX = (GameConstants::WINDOW_WIDTH - GameConstants::BUTTON_WIDTH) / 2;
    int lineY = 190;
    line(lineX, lineY, lineX + GameConstants::BUTTON_WIDTH, lineY);

    // 动态更新难度按钮（不同难度不同颜色）
    const wchar_t* diffNames[] = { L"难度: 简单", L"难度: 困难", L"难度: 地狱" };
    COLORREF diffNormal[] = { RGB(60, 140, 60),  RGB(180, 160, 40),  RGB(180, 50, 50) };
    COLORREF diffHover[]  = { RGB(90, 190, 90),  RGB(230, 200, 60),  RGB(230, 70, 70) };
    int idx = difficultyIndex;
    buttons[BTN_SETTINGS].Init((GameConstants::WINDOW_WIDTH - GameConstants::BUTTON_WIDTH) / 2,
        280 + 80 * 2,
        GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        diffNames[idx], diffNormal[idx], diffHover[idx], GameConstants::COLOR_BUTTON_TEXT);

    // 按钮
    for (int i = 0; i < BTN_COUNT; i++) {
        buttons[i].Render();
    }

    // 底部提示
    settextcolor(RGB(100, 100, 100));
    settextstyle(16, 0, _T("微软雅黑"));
    const wchar_t* footer = L"PVZ2677 项目组  |  EasyX 暑期课程";
    int fw = textwidth(footer);
    outtextxy((GameConstants::WINDOW_WIDTH - fw) / 2, GameConstants::WINDOW_HEIGHT - 40, footer);
}
