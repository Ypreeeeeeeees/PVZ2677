#include "system/WaveManager.h"
#include "core/Game.h"
#include "entity/Zombie.h"
#include "entity/NormalZombie.h"
#include "entity/BucketZombie.h"
#include "utils/Constants.h"
#include <cstdlib>
#include <cmath>

WaveManager::WaveManager()
    : totalWaves(0), currentWave(0), waveTimer(0.0f) {
}

void WaveManager::Init(int totalWaves, Difficulty difficulty) {
    this->totalWaves = totalWaves;
    currentWave = 0;
    waveTimer = 10.0f;

    // 难度倍率：Easy=1.0, Hard=1.5, Hell=1.5^2=2.25
    float scale = 1.0f;
    for (int d = 0; d < static_cast<int>(difficulty); d++) {
        scale *= 1.5f;
    }

    waves.clear();
    for (int i = 0; i < totalWaves; i++) {
        WaveEntry w;
        w.spawnTime = 15.0f;

        int baseNormal = 0;
        if (i == 0)      baseNormal = 1;
        else if (i == 1) baseNormal = 2;
        else if (i == 2) baseNormal = 2;
        else if (i == 3) baseNormal = 3;
        else             baseNormal = 4;

        int baseBucket = 0;
        if (i == 4)      baseBucket = 2;
        else if (i >= 2) baseBucket = 1;
        else             baseBucket = 0;

        w.normalCount = static_cast<int>(std::ceil(baseNormal * scale));
        w.bucketCount = static_cast<int>(std::ceil(baseBucket * scale));

        waves.push_back(w);
    }
}

void WaveManager::Update(float dt, std::vector<std::unique_ptr<Zombie>>& zombies, int mapRows) {
    if (currentWave >= totalWaves) return;

    waveTimer -= dt;
    if (waveTimer <= 0.0f) {
        SpawnWave(zombies, mapRows);
    }
}

void WaveManager::SpawnWave(std::vector<std::unique_ptr<Zombie>>& zombies, int mapRows) {
    if (currentWave >= totalWaves) return;

    WaveEntry& w = waves[currentWave];
    float startX = static_cast<float>(GameConstants::WINDOW_WIDTH + 50);
    int cellSize = GameConstants::CELL_SIZE;
    int offsetY = GameConstants::MAP_OFFSET_Y;

    for (int i = 0; i < w.normalCount; i++) {
        int row = rand() % mapRows;
        float y = static_cast<float>(offsetY + row * cellSize);  // 行顶部
        float x = startX + i * 80.0f;
        zombies.push_back(std::make_unique<NormalZombie>(row, x, y));
    }

    for (int i = 0; i < w.bucketCount; i++) {
        int row = rand() % mapRows;
        float y = static_cast<float>(offsetY + row * cellSize);  // 行顶部
        float x = startX + (w.normalCount + i) * 80.0f;
        zombies.push_back(std::make_unique<BucketZombie>(row, x, y));
    }

    currentWave++;
    if (currentWave < totalWaves) {
        waveTimer = waves[currentWave].spawnTime;
    }
}
