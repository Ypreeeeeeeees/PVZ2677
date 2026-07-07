#include "scene/HelpScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "utils/Constants.h"

HelpScene::HelpScene() {
    sceneID = SceneID::Help;
}

void HelpScene::OnEnter() {
    backButton.Init(40, GameConstants::WINDOW_HEIGHT - 70,
        GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"返回", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);
}

void HelpScene::OnExit() {
}

void HelpScene::Update(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();
    backButton.Update(input.GetMouseX(), input.GetMouseY(),
        input.IsMouseDown(), input.IsMouseClicked());

    if (backButton.IsClicked()) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void HelpScene::Render() {
    cleardevice();
    setbkcolor(RGB(30, 60, 25));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    settextcolor(GameConstants::COLOR_TITLE);
    settextstyle(40, 0, _T("微软雅黑"));
    const wchar_t* title = L"游戏说明";
    outtextxy(40, 30, title);

    // 分隔线
    setlinecolor(GameConstants::COLOR_TITLE);
    line(40, 80, GameConstants::WINDOW_WIDTH - 40, 80);

    // 说明文字
    settextcolor(RGB(220, 220, 220));
    settextstyle(22, 0, _T("微软雅黑"));
    int y = 110;
    int lineHeight = 35;

    const wchar_t* lines[] = {
        L"【游戏目标】",
        L"  通过种植植物来抵御僵尸的进攻，保护你的房子不被入侵。",
        L"",
        L"【操作方式】",
        L"  鼠标点击卡槽选择植物 → 移动到地图有效格子 → 点击种植",
        L"  点击阳光即可收集资源",
        L"  按 ESC 键暂停游戏",
        L"",
        L"【植物介绍】",
        L"  向日葵 - 花费 50 阳光 | 产生额外阳光资源",
        L"  豌豆射手 - 花费 100 阳光 | 发射豌豆攻击同一行的僵尸",
        L"",
        L"【僵尸介绍】",
        L"  普通僵尸 - 生命 200 | 移动速度较慢",
        L"  铁桶僵尸 - 生命 600 | 拥有铁桶护甲",
        L"",
        L"【胜负条件】",
        L"  胜利：消灭所有波次的僵尸",
        L"  失败：任意僵尸进入房子",
    };

    for (auto& line : lines) {
        outtextxy(40, y, line);
        y += lineHeight;
    }

    backButton.Render();
}
