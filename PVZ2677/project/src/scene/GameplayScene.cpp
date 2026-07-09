#include "scene/GameplayScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "entity/Plant.h"
#include "entity/SunFlower.h"
#include "entity/PeaShooter.h"
#include "entity/WallNut.h"
#include "entity/Zombie.h"
#include "entity/Bullet.h"
#include "entity/Sun.h"
#include "entity/LawnMower.h"
#include "utils/Constants.h"
#include <graphics.h>
#include <cstdlib>
#include <ctime>

GameplayScene::GameplayScene()
    : plantingType(CardType::SunFlower), isPlanting(false),
      plantLockFrame(false), isShovelMode(false),
      shovelX(0), shovelY(0), shovelW(0), shovelH(0),
      naturalSunTimer(0.0f), gameState(0) {
    sceneID = SceneID::Gameplay;
}

void GameplayScene::OnEnter() {
    map.Init(GameConstants::MAP_ROWS, GameConstants::MAP_COLS,
             GameConstants::CELL_SIZE,
             GameConstants::MAP_OFFSET_X, GameConstants::MAP_OFFSET_Y,
             GameConstants::HOUSE_BOUNDARY_X);

    hud = HUD();
    gameState = 0;
    isPlanting = false;
    isShovelMode = false;
    isPaused = false;
    naturalSunTimer = 0.0f;

    // 铲子按钮位置（卡片栏右侧）
    shovelX = 470;
    shovelY = 10;
    shovelW = 40;
    shovelH = 85;

    srand(static_cast<unsigned>(time(nullptr)));

    // 初始化卡槽
    cards[0].Init(CardType::SunFlower, L"向日葵",
        GameConstants::SUNFLOWER_PRICE, GameConstants::SUNFLOWER_COOLDOWN,
        200, 10, 80, 85);
    cards[1].Init(CardType::PeaShooter, L"豌豆射手",
        GameConstants::PEASHOOTER_PRICE, GameConstants::PEASHOOTER_COOLDOWN,
        290, 10, 80, 85);
    cards[2].Init(CardType::WallNut, L"坚果墙",
        GameConstants::WALLNUT_PRICE, GameConstants::WALLNUT_COOLDOWN,
        380, 10, 80, 85);

    // 初始化暂停按钮
    pauseContinueBtn.Init(540, 280, GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"继续游戏", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);
    pauseMenuBtn.Init(540, 370, GameConstants::BUTTON_WIDTH, GameConstants::BUTTON_HEIGHT,
        L"返回主菜单", GameConstants::COLOR_BUTTON_NORMAL,
        GameConstants::COLOR_BUTTON_HOVER, GameConstants::COLOR_BUTTON_TEXT);

    // 初始化波次
    waveManager.Init(5, Game::GetInstance().GetDifficulty());

    // 初始化小推车
    lawnMowers.clear();
    for (int r = 0; r < GameConstants::MAP_ROWS; r++) {
        float mowerY = static_cast<float>(GameConstants::MAP_OFFSET_Y + r * GameConstants::CELL_SIZE);
        lawnMowers.push_back(std::make_unique<LawnMower>(
            r, static_cast<float>(GameConstants::HOUSE_BOUNDARY_X + 20),
            mowerY, GameConstants::LAWNMOWER_SPEED));
    }

    // 清空实体
    plants.clear();
    zombies.clear();
    bullets.clear();
    suns.clear();
}

void GameplayScene::OnExit() {
    plants.clear();
    zombies.clear();
    bullets.clear();
    suns.clear();
    lawnMowers.clear();
}

void GameplayScene::Update(float dt) {
    // 胜负场景切换（正常流程）
    if (gameState != 0 && !isPaused) {
        if (gameState == 1) {
            int mowers = 0;
            for (auto& m : lawnMowers) {
                if (m->GetState() == LawnMowerState::Idle) mowers++;
            }
            Game::GetInstance().SetVictoryInfo(mowers);
            Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Victory);
        } else {
            Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Defeat);
        }
        return;
    }

    if (isPaused) {
        HandlePauseInput(dt);
        return;
    }

    HandleInput(dt);
    UpdateSunSystem(dt);
    waveManager.Update(dt, zombies, GameConstants::MAP_ROWS);

    int waveNow = waveManager.GetCurrentWave();
    if (waveNow > lastWaveAnnounced && waveNow <= waveManager.GetTotalWaves()) {
        lastWaveAnnounced = waveNow;
        waveAnnouncementTimer = 2.0f;
    }
    if (waveAnnouncementTimer > 0.0f) {
        waveAnnouncementTimer -= dt;
    }

    hud.SetWaveInfo(waveManager.GetCurrentWave(), waveManager.GetTotalWaves());
    UpdateEntities(dt);
    CheckCollisions();
    CheckLawnMowers();
    CleanupDead();
    CheckWinLose();
}

void GameplayScene::HandlePauseInput(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();

    if (pauseLockFrame) {
        pauseLockFrame = false;
        return;
    }

    int mx = input.GetMouseX();
    int my = input.GetMouseY();
    pauseContinueBtn.Update(mx, my, input.IsMouseDown(), input.IsMouseClicked());
    pauseMenuBtn.Update(mx, my, input.IsMouseDown(), input.IsMouseClicked());

    if (pauseContinueBtn.IsClicked() || input.IsKeyPressed(VK_ESCAPE)) {
        isPaused = false;
        return;
    }

    if (pauseMenuBtn.IsClicked()) {
        // 返回主菜单前清空（正常流程）
        plants.clear();
        zombies.clear();
        bullets.clear();
        suns.clear();
        lawnMowers.clear();
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Menu);
    }
}

void GameplayScene::HandleInput(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();
    int mx = input.GetMouseX();
    int my = input.GetMouseY();

    // ESC 暂停（内嵌，不切换场景）
    if (input.IsKeyPressed(VK_ESCAPE)) {
        if (isPlanting) isPlanting = false;
        isPaused = true;
        pauseLockFrame = true;
        return;
    }

    if (isPlanting) {
        if (plantLockFrame) {
            plantLockFrame = false;
            return;
        }
        if (input.IsMouseClicked() && mx < GameConstants::MAP_OFFSET_X) {
            isPlanting = false;
            return;
        }
        if (input.IsMouseClicked() &&
            my >= GameConstants::MAP_OFFSET_Y &&
            my <= GameConstants::MAP_OFFSET_Y + GameConstants::MAP_GRID_HEIGHT) {
            TryPlant(mx, my);
        }
        return;
    }

    // 铲子模式
    if (isShovelMode) {
        if (input.IsMouseClicked()) {
            if (my >= GameConstants::MAP_OFFSET_Y &&
                my <= GameConstants::MAP_OFFSET_Y + GameConstants::MAP_GRID_HEIGHT) {
                CellPos cell = map.ScreenToCell(mx, my);
                if (map.IsValidCell(cell.row, cell.col) && !map.CanPlant(cell.row, cell.col)) {
                    Plant* plant = map.GetPlant(cell.row, cell.col);
                    if (plant) {
                        hud.AddSun(plant->GetPrice() / 2);
                        plants.erase(std::remove_if(plants.begin(), plants.end(),
                            [&](const auto& p) { return p.get() == plant; }), plants.end());
                        map.RemovePlant(cell.row, cell.col);
                    }
                }
            }
            isShovelMode = false;
        }
        return;
    }

    // 铲子按钮点击
    if (input.IsMouseClicked() &&
        mx >= shovelX && mx <= shovelX + shovelW &&
        my >= shovelY && my <= shovelY + shovelH) {
        isShovelMode = true;
        return;
    }

    // 卡片点击
    for (int i = 0; i < 3; i++) {
        cards[i].Update(dt, hud.GetSunCount());
        if (cards[i].IsClicked(mx, my, input.IsMouseClicked())) {
            StartPlanting(cards[i].GetType());
            return;
        }
    }

    // 阳光收集
    if (input.IsMouseClicked()) {
        for (auto& sun : suns) {
            if (!sun->IsCollectible()) continue;
            int sx = static_cast<int>(sun->GetX());
            int sy = static_cast<int>(sun->GetY());
            if (mx >= sx - 20 && mx <= sx + 20 &&
                my >= sy - 20 && my <= sy + 20) {
                sun->Collect();
                hud.AddSun(sun->GetValue());
            }
        }
    }
}

void GameplayScene::StartPlanting(CardType type) {
    int price = 0;
    int cardIndex = 0;
    if (type == CardType::SunFlower) { price = GameConstants::SUNFLOWER_PRICE; cardIndex = 0; }
    else if (type == CardType::PeaShooter) { price = GameConstants::PEASHOOTER_PRICE; cardIndex = 1; }
    else if (type == CardType::WallNut) { price = GameConstants::WALLNUT_PRICE; cardIndex = 2; }

    if (!hud.SpendSun(price)) return;
    cards[cardIndex].StartCooldown();

    plantingType = type;
    isPlanting = true;
    plantLockFrame = true;
}

void GameplayScene::TryPlant(int screenX, int screenY) {
    CellPos cell = map.ScreenToCell(screenX, screenY);
    if (!map.IsValidCell(cell.row, cell.col)) { isPlanting = false; return; }
    if (!map.CanPlant(cell.row, cell.col)) return;

    if (plantingType == CardType::SunFlower) {
        auto plant = std::make_unique<SunFlower>(cell.row, cell.col);
        map.PlantAt(cell.row, cell.col, plant.get());
        plants.push_back(std::move(plant));
    } else if (plantingType == CardType::PeaShooter) {
        auto plant = std::make_unique<PeaShooter>(cell.row, cell.col);
        map.PlantAt(cell.row, cell.col, plant.get());
        plants.push_back(std::move(plant));
    } else if (plantingType == CardType::WallNut) {
        auto plant = std::make_unique<WallNut>(cell.row, cell.col);
        map.PlantAt(cell.row, cell.col, plant.get());
        plants.push_back(std::move(plant));
    }

    isPlanting = false;
}

void GameplayScene::UpdateSunSystem(float dt) {
    naturalSunTimer += dt;
    if (naturalSunTimer >= GameConstants::NATURAL_SUN_INTERVAL) {
        naturalSunTimer = 0.0f;
        int col = rand() % GameConstants::MAP_COLS;
        Point pt = map.CellToScreen(0, col);
        auto s = std::make_unique<Sun>(static_cast<float>(pt.x), 0.0f, GameConstants::SUN_VALUE);
        s->SetFalling(true);
        s->SetTargetY(static_cast<float>(pt.y));
        suns.push_back(std::move(s));
    }

    for (auto& plant : plants) {
        if (!plant->IsAlive() || plant->GetName() != L"向日葵") continue;
        SunFlower* sf = static_cast<SunFlower*>(plant.get());
        if (sf->CanProduceSun()) {
            sf->ResetSunTimer();
            Point pt = map.CellToScreen(plant->GetRow(), plant->GetCol());
            suns.push_back(std::make_unique<Sun>(
                static_cast<float>(pt.x), static_cast<float>(pt.y - 10), GameConstants::SUN_VALUE));
        }
    }

    for (auto& sun : suns) sun->Update(dt);
}

void GameplayScene::UpdateEntities(float dt) {
    for (auto& plant : plants) plant->Update(dt);

    for (auto& plant : plants) {
        if (!plant->IsAlive() || plant->GetName() != L"豌豆射手") continue;
        PeaShooter* ps = static_cast<PeaShooter*>(plant.get());
        if (ps->CanShoot()) {
            ps->ResetAttackTimer();
            Point pt = map.CellToScreen(plant->GetRow(), plant->GetCol());
            bullets.push_back(std::make_unique<Bullet>(
                plant->GetRow(), static_cast<float>(pt.x + 25), static_cast<float>(pt.y),
                GameConstants::PEA_SPEED, GameConstants::PEA_DAMAGE));
        }
    }

    for (auto& zombie : zombies) zombie->Update(dt);
    for (auto& bullet : bullets) bullet->Update(dt);
    for (auto& mower : lawnMowers) mower->Update(dt);

    for (auto& zombie : zombies) {
        if (zombie->IsAlive() && map.HasZombieReachedHouse(zombie->GetX())) {
            gameState = 2;
            return;
        }
    }
}

void GameplayScene::CheckCollisions() {
    collisionManager.CheckZombiePlant(zombies, map);
    collisionManager.CheckBulletZombie(bullets, zombies);

    for (auto& zombie : zombies) {
        if (!zombie->IsAlive() || !zombie->IsAttacking()) continue;
        if (!zombie->CanDealDamage()) continue;

        int row = zombie->GetRow();
        float zx = zombie->GetX();
        for (auto& plant : plants) {
            if (!plant->IsAlive() || plant->GetState() == PlantState::Dead || plant->GetRow() != row) continue;
            Point pt = map.CellToScreen(plant->GetRow(), plant->GetCol());
            int pw = GameConstants::CELL_SIZE * 2 / 3;
            if (zx <= pt.x + pw / 2) {
                plant->TakeDamage(zombie->GetAttackPower());
                zombie->ResetDamageFlag();
                break;
            }
        }
    }
}

void GameplayScene::CheckLawnMowers() {
    for (auto& mower : lawnMowers) {
        if (mower->GetState() != LawnMowerState::Idle) continue;
        int row = mower->GetRow();
        float triggerX = GameConstants::LAWNMOWER_TRIGGER_X;
        for (auto& zombie : zombies) {
            if (!zombie->IsAlive() || zombie->GetRow() != row) continue;
            if (zombie->GetX() <= triggerX) { mower->Trigger(); break; }
        }
    }

    for (auto& mower : lawnMowers) {
        if (mower->GetState() != LawnMowerState::Moving) continue;
        int row = mower->GetRow();
        float mowerX = mower->GetX();
        for (auto& zombie : zombies) {
            if (!zombie->IsAlive() || zombie->GetRow() != row) continue;
            if (zombie->GetX() >= mowerX - 10 && zombie->GetX() <= mowerX + 60)
                zombie->TakeDamage(9999);
        }
    }
}

void GameplayScene::CleanupDead() {
    plants.erase(std::remove_if(plants.begin(), plants.end(),
        [this](const auto& p) {
            if (!p->IsAlive() && p->GetState() == PlantState::Dead) {
                map.RemovePlant(p->GetRow(), p->GetCol());
                return true;
            }
            return false;
        }), plants.end());

    zombies.erase(std::remove_if(zombies.begin(), zombies.end(),
        [](const auto& z) { return !z->IsAlive(); }), zombies.end());

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const auto& b) { return !b->IsAlive(); }), bullets.end());

    suns.erase(std::remove_if(suns.begin(), suns.end(),
        [](const auto& s) { return !s->IsAlive(); }), suns.end());

    lawnMowers.erase(std::remove_if(lawnMowers.begin(), lawnMowers.end(),
        [](const auto& m) { return m->GetState() == LawnMowerState::Gone; }), lawnMowers.end());
}

void GameplayScene::CheckWinLose() {
    if (waveManager.IsAllWavesFinished() && zombies.empty()) {
        gameState = 1;
    }
}

void GameplayScene::Render() {
    cleardevice();
    setbkcolor(RGB(60, 120, 40));
    cleardevice();

    map.Render();

    if (isPlanting) {
        InputManager& input = Game::GetInstance().GetInputManager();
        CellPos cell = map.ScreenToCell(input.GetMouseX(), input.GetMouseY());
        if (map.IsValidCell(cell.row, cell.col)) {
            Point pt = map.CellToScreen(cell.row, cell.col);
            int s = GameConstants::CELL_SIZE * 2 / 3;
            int cx = pt.x - s / 2;
            int cy = pt.y - s / 2;
            COLORREF color = map.CanPlant(cell.row, cell.col) ? RGB(100, 255, 100) : RGB(255, 100, 100);
            setfillcolor(color);
            solidroundrect(cx, cy, cx + s, cy + s, 5, 5);
        }
    }

    for (auto& plant : plants) {
        if (!plant->IsAlive()) continue;
        Point pt = map.CellToScreen(plant->GetRow(), plant->GetCol());
        int s = GameConstants::CELL_SIZE * 2 / 3;
        int cx = pt.x - s / 2;
        int cy = pt.y - s / 2;

        if (plant->GetName() == L"向日葵") {
            setfillcolor(RGB(255, 220, 50));
            solidroundrect(cx, cy, cx + s, cy + s, 6, 6);
            setfillcolor(RGB(150, 100, 20));
            solidcircle(pt.x, pt.y, s / 4);
        } else if (plant->GetName() == L"豌豆射手") {
            setfillcolor(RGB(80, 200, 80));
            solidroundrect(cx, cy, cx + s, cy + s, 6, 6);
            setfillcolor(RGB(30, 100, 30));
            solidrectangle(pt.x + s / 4, pt.y - 4, pt.x + s / 2, pt.y + 4);
        } else if (plant->GetName() == L"坚果墙") {
            setfillcolor(RGB(160, 120, 70));
            solidroundrect(cx, cy, cx + s, cy + s, 8, 8);
            setfillcolor(RGB(60, 40, 20));
            solidcircle(pt.x - s / 6, pt.y - s / 6, 4);
            solidcircle(pt.x + s / 6, pt.y - s / 6, 4);
            solidcircle(pt.x, pt.y + s / 5, 4);
        }

        if (plant->GetHealth() < plant->GetMaxHealth()) {
            int barW = s;
            int barH = 6;
            int barX = cx;
            int barY = cy - 10;
            float ratio = static_cast<float>(plant->GetHealth()) / static_cast<float>(plant->GetMaxHealth());
            int fillW = static_cast<int>(barW * ratio);
            setfillcolor(RGB(60, 60, 60));
            solidrectangle(barX, barY, barX + barW, barY + barH);
            COLORREF hpColor = (ratio > 0.5f) ? RGB(100, 220, 80)
                             : (ratio > 0.25f) ? RGB(220, 200, 50)
                             : RGB(220, 60, 60);
            setfillcolor(hpColor);
            solidrectangle(barX, barY, barX + fillW, barY + barH);
        }
    }

    for (auto& zombie : zombies) zombie->Render();
    for (auto& mower : lawnMowers) mower->Render();
    for (auto& bullet : bullets) bullet->Render();
    for (auto& sun : suns) sun->Render();

    setfillcolor(RGB(40, 30, 20));
    solidrectangle(0, 0, GameConstants::WINDOW_WIDTH, GameConstants::MAP_OFFSET_Y);

    for (int i = 0; i < 3; i++) cards[i].Render();

    {
        COLORREF shovelBg = isShovelMode ? RGB(180, 140, 80) : RGB(100, 80, 50);
        setfillcolor(shovelBg);
        solidroundrect(shovelX, shovelY, shovelX + shovelW, shovelY + shovelH, 4, 4);
        setlinecolor(RGB(120, 100, 60));
        setlinestyle(PS_SOLID, 1);
        rectangle(shovelX, shovelY, shovelX + shovelW, shovelY + shovelH);
        setfillcolor(RGB(200, 160, 100));
        int cx = shovelX + shovelW / 2;
        solidrectangle(cx - 2, shovelY + 10, cx + 2, shovelY + 60);
        solidrectangle(cx - 8, shovelY + 55, cx + 8, shovelY + 65);
    }

    hud.Render();

    if (waveAnnouncementTimer > 0.0f) {
        std::wstring waveText = L"第 " + std::to_wstring(waveManager.GetCurrentWave()) + L" 波僵尸来袭!";
        int alpha = static_cast<int>(waveAnnouncementTimer * 127);
        if (alpha > 255) alpha = 255;
        settextcolor(RGB(255, 100 + alpha / 3, 50));
        settextstyle(40, 0, _T("微软雅黑"));
        setbkmode(TRANSPARENT);
        int tw = textwidth(waveText.c_str());
        outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, GameConstants::WINDOW_HEIGHT / 2 - 20, waveText.c_str());
    }

    // 暂停遮罩（在最上层）
    if (isPaused) {
        setfillcolor(RGB(80, 80, 80));
        solidrectangle(0, 0, GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT);
        setbkmode(TRANSPARENT);
        settextcolor(GameConstants::COLOR_TITLE);
        settextstyle(48, 0, _T("微软雅黑"));
        const wchar_t* title = L"暂停";
        int tw = textwidth(title);
        outtextxy((GameConstants::WINDOW_WIDTH - tw) / 2, 140, title);
        pauseContinueBtn.Render();
        pauseMenuBtn.Render();
    }
}
