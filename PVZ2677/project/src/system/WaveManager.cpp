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
        w.normalCount = 1 + i;
        w.bucketCount = (i >= 2) ? 1 : 0;
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
