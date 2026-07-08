#ifndef PVZ_WAVEMANAGER_H
#define PVZ_WAVEMANAGER_H

#include <vector>
#include <memory>

enum class Difficulty;

class Zombie;

struct WaveEntry {
    float spawnTime;
    int normalCount;
    int bucketCount;
};

class WaveManager {
public:
    WaveManager();

    void Init(int totalWaves, Difficulty difficulty);
    void Update(float dt, std::vector<std::unique_ptr<Zombie>>& zombies, int mapRows);
    bool IsAllWavesFinished() const { return currentWave >= totalWaves; }
    int  GetCurrentWave() const { return currentWave; }
    int  GetTotalWaves() const  { return totalWaves; }

private:
    void SpawnWave(std::vector<std::unique_ptr<Zombie>>& zombies, int mapRows);

    std::vector<WaveEntry> waves;
    int totalWaves;
    int currentWave;
    float waveTimer;
};

#endif // PVZ_WAVEMANAGER_H
