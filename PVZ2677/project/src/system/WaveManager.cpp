#include "system/WaveManager.h"
#include "entity/Zombie.h"
#include "entity/NormalZombie.h"
#include "entity/BucketZombie.h"
#include "utils/Constants.h"
#include <cstdlib>

WaveManager::WaveManager()
    : totalWaves(0), currentWave(0), waveTimer(0.0f) {
}

void WaveManager::Init(int totalWaves) {
    this->totalWaves = totalWaves;
    currentWave = 0;
    waveTimer = 10.0f;

    waves.clear();
    for (int i = 0; i < totalWaves; i++) {
        WaveEntry w;
        w.spawnTime = 15.0f;
        // 递增平缓：第1波1个 → 第2波2个 → 第3~4波2~3个 → 最终波4个
        if (i == 0)      w.normalCount = 1;
        else if (i == 1) w.normalCount = 2;
        else if (i == 2) w.normalCount = 2;
        else if (i == 3) w.normalCount = 3;
        else             w.normalCount = 4;

        // 铁桶僵尸从第3波起每波1个，最终波2个
        if (i == 4)      w.bucketCount = 2;
        else if (i >= 2) w.bucketCount = 1;
        else             w.bucketCount = 0;

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
