#ifndef PVZ_GAMEPLAYSCENE_H
#define PVZ_GAMEPLAYSCENE_H

#include "core/Scene.h"
#include "component/Card.h"
#include "component/HUD.h"
#include "system/Map.h"
#include "system/CollisionManager.h"
#include "system/WaveManager.h"
#include <vector>
#include <memory>

class Plant;
class Zombie;
class Bullet;
class Sun;
class LawnMower;
class SunFlower;
class PeaShooter;

class GameplayScene : public Scene {
public:
    GameplayScene();

    void OnEnter() override;
    void OnExit() override;
    void Update(float dt) override;
    void Render() override;

private:
    void HandleInput(float dt);
    void UpdateSunSystem(float dt);
    void UpdateEntities(float dt);
    void CheckCollisions();
    void CheckLawnMowers();
    void CleanupDead();
    void CheckWinLose();

    // 种植
    void StartPlanting(CardType type);
    void TryPlant(int screenX, int screenY);

    Map map;
    HUD hud;
    Card cards[3];          // 向日葵、豌豆射手、坚果墙
    CollisionManager collisionManager;
    WaveManager waveManager;

    std::vector<std::unique_ptr<Plant>> plants;
    std::vector<std::unique_ptr<Zombie>> zombies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Sun>> suns;
    std::vector<std::unique_ptr<LawnMower>> lawnMowers;

    CardType plantingType;   // 当前种植模式下的植物类型
    bool isPlanting;         // 是否在种植模式中
    bool plantLockFrame;     // 进入种植模式的首帧锁定
    bool isShovelMode;       // 铲子模式
    int  shovelX, shovelY, shovelW, shovelH;  // 铲子按钮区域
    float naturalSunTimer;   // 自然阳光计时器
    int gameState;           // 0=进行中, 1=胜利, 2=失败
    float waveAnnouncementTimer = 0.0f;  // 新波次提示计时器
    int   lastWaveAnnounced = 0;         // 上轮已提示到的波次
};

#endif // PVZ_GAMEPLAYSCENE_H
