#include "scene/GameplayScene.h"
#include "core/Game.h"
#include "core/SceneManager.h"
#include "system/InputManager.h"
#include "entity/Plant.h"
#include "entity/SunFlower.h"
#include "entity/PeaShooter.h"
#include "entity/Zombie.h"
#include "entity/Bullet.h"
#include "entity/Sun.h"
#include "utils/Constants.h"
#include <graphics.h>
#include <cstdlib>
#include <ctime>

GameplayScene::GameplayScene()
    : plantingType(CardType::SunFlower), isPlanting(false),
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
    naturalSunTimer = 0.0f;

    srand(static_cast<unsigned>(time(nullptr)));

    // 初始化卡槽
    cards[0].Init(CardType::SunFlower, L"向日葵",
        GameConstants::SUNFLOWER_PRICE, GameConstants::SUNFLOWER_COOLDOWN,
        200, 10, 80, 85);
    cards[1].Init(CardType::PeaShooter, L"豌豆射手",
        GameConstants::PEASHOOTER_PRICE, GameConstants::PEASHOOTER_COOLDOWN,
        290, 10, 80, 85);

    // 初始化波次
    waveManager.Init(5);

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
}

void GameplayScene::Update(float dt) {
    if (gameState != 0) {
        if (gameState == 1) {
            Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Victory);
        } else {
            Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Defeat);
        }
        return;
    }

    HandleInput(dt);
    UpdateSunSystem(dt);
    waveManager.Update(dt, zombies, GameConstants::MAP_ROWS);
    UpdateEntities(dt);
    CheckCollisions();
    CleanupDead();
    CheckWinLose();
}

void GameplayScene::HandleInput(float dt) {
    InputManager& input = Game::GetInstance().GetInputManager();
    int mx = input.GetMouseX();
    int my = input.GetMouseY();

    // ESC 暂停
    if (input.IsKeyPressed(VK_ESCAPE)) {
        Game::GetInstance().GetSceneManager().SwitchTo(SceneID::Pause);
        return;
    }

    if (isPlanting) {
        // 右键取消种植
        if (input.IsMouseClicked() && mx < GameConstants::MAP_OFFSET_X) {
            isPlanting = false;
        } else if (input.IsMouseClicked()) {
            TryPlant(mx, my);
        }
        return;
    }

    // 卡片点击
    for (int i = 0; i < 2; i++) {
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
    if (!hud.SpendSun((type == CardType::SunFlower)
        ? GameConstants::SUNFLOWER_PRICE : GameConstants::PEASHOOTER_PRICE)) {
        return;
    }

    if (type == CardType::SunFlower) {
        cards[0].StartCooldown();
    } else {
        cards[1].StartCooldown();
    }

    plantingType = type;
    isPlanting = true;
}

void GameplayScene::TryPlant(int screenX, int screenY) {
    CellPos cell = map.ScreenToCell(screenX, screenY);
    if (!map.IsValidCell(cell.row, cell.col)) {
        isPlanting = false;
        return;
    }
    if (!map.CanPlant(cell.row, cell.col)) {
        return;
    }

    if (plantingType == CardType::SunFlower) {
        auto plant = std::make_unique<SunFlower>(cell.row, cell.col);
        map.PlantAt(cell.row, cell.col, plant.get());
        plants.push_back(std::move(plant));
    } else if (plantingType == CardType::PeaShooter) {
        auto plant = std::make_unique<PeaShooter>(cell.row, cell.col);
        map.PlantAt(cell.row, cell.col, plant.get());
        plants.push_back(std::move(plant));
    }

    isPlanting = false;
}

void GameplayScene::UpdateSunSystem(float dt) {
    // 自然阳光
    naturalSunTimer += dt;
    if (naturalSunTimer >= GameConstants::NATURAL_SUN_INTERVAL) {
        naturalSunTimer = 0.0f;
        int col = rand() % GameConstants::MAP_COLS;
        Point pt = map.CellToScreen(0, col);
        auto s = std::make_unique<Sun>(static_cast<float>(pt.x), 0.0f,
                                       GameConstants::SUN_VALUE);
        s->SetFalling(true);
        s->SetTargetY(static_cast<float>(pt.y));
        suns.push_back(std::move(s));
    }

    // 向日葵产出阳光
    for (auto& plant : plants) {
        if (!plant->IsAlive() || plant->GetName() != L"向日葵") continue;
        SunFlower* sf = static_cast<SunFlower*>(plant.get());
        if (sf->CanProduceSun()) {
            sf->ResetSunTimer();
            Point pt = map.CellToScreen(plant->GetRow(), plant->GetCol());
            suns.push_back(std::make_unique<Sun>(
                static_cast<float>(pt.x), static_cast<float>(pt.y - 10),
                GameConstants::SUN_VALUE));
        }
    }

    // 阳光实体更新 + 超时清理
    for (auto& sun : suns) {
        sun->Update(dt);
    }
}

void GameplayScene::UpdateEntities(float dt) {
    // 植物更新
    for (auto& plant : plants) {
        plant->Update(dt);
    }

    // 豌豆射手发射
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

    // 僵尸更新
    for (auto& zombie : zombies) {
        zombie->Update(dt);
    }

    // 子弹更新
    for (auto& bullet : bullets) {
        bullet->Update(dt);
    }

    // 检查僵尸是否到达房子
    for (auto& zombie : zombies) {
        if (zombie->IsAlive() &&
            map.HasZombieReachedHouse(zombie->GetX())) {
            gameState = 2;
            return;
        }
    }
}

void GameplayScene::CheckCollisions() {
    collisionManager.CheckZombiePlant(zombies, map);
    collisionManager.CheckBulletZombie(bullets, zombies);

    // 僵尸攻击植物：在 Walking 状态进入 Attacking 触发
    for (auto& zombie : zombies) {
        if (!zombie->IsAlive()) continue;
        if (!zombie->IsAttacking()) continue;

        int row = zombie->GetRow();
        float zx = zombie->GetX();
        for (auto& plant : plants) {
            if (!plant->IsAlive() || plant->GetRow() != row) continue;
            Point pt = map.CellToScreen(plant->GetRow(), plant->GetCol());
            int pw = GameConstants::CELL_SIZE * 2 / 3;
            if (zx <= pt.x + pw / 2) {
                plant->TakeDamage(static_cast<int>(zombie->GetAttackPower() * 0.016f));
                break;
            }
        }
    }
}

void GameplayScene::CleanupDead() {
    // 清除死亡植物
    plants.erase(std::remove_if(plants.begin(), plants.end(),
        [](const auto& p) {
            return !p->IsAlive() && p->GetState() == PlantState::Dead;
        }), plants.end());

    // 清除死亡僵尸
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(),
        [](const auto& z) { return !z->IsAlive(); }), zombies.end());

    // 清除死亡/离屏子弹
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const auto& b) { return !b->IsAlive(); }), bullets.end());

    // 清除消失的阳光
    suns.erase(std::remove_if(suns.begin(), suns.end(),
        [](const auto& s) { return !s->IsAlive(); }), suns.end());
}

void GameplayScene::CheckWinLose() {
    if (waveManager.IsAllWavesFinished() && zombies.empty()) {
        gameState = 1;
    }
}

void GameplayScene::Render() {
    cleardevice();

    // 背景
    setbkcolor(RGB(60, 120, 40));
    cleardevice();

    // 地图
    map.Render();

    // 种植预览
    if (isPlanting) {
        InputManager& input = Game::GetInstance().GetInputManager();
        CellPos cell = map.ScreenToCell(input.GetMouseX(), input.GetMouseY());
        if (map.IsValidCell(cell.row, cell.col)) {
            Point pt = map.CellToScreen(cell.row, cell.col);
            int s = GameConstants::CELL_SIZE * 2 / 3;
            int cx = pt.x - s / 2;
            int cy = pt.y - s / 2;
            COLORREF color = map.CanPlant(cell.row, cell.col)
                ? RGB(100, 255, 100) : RGB(255, 100, 100);
            setfillcolor(color);
            solidroundrect(cx, cy, cx + s, cy + s, 5, 5);
        }
    }

    // 植物
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
        }
    }

    // 僵尸
    for (auto& zombie : zombies) {
        zombie->Render();
    }

    // 子弹
    for (auto& bullet : bullets) {
        bullet->Render();
    }

    // 阳光
    for (auto& sun : suns) {
        sun->Render();
    }

    // 卡槽背景
    setfillcolor(RGB(40, 30, 20));
    solidrectangle(0, 0, GameConstants::WINDOW_WIDTH, GameConstants::MAP_OFFSET_Y);

    // 卡片
    for (int i = 0; i < 2; i++) {
        cards[i].Render();
    }

    // HUD
    hud.Render();
}
