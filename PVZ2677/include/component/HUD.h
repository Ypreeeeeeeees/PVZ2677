#ifndef PVZ_HUD_H
#define PVZ_HUD_H

class HUD {
public:
    HUD();

    void SetSunCount(int count) { sunCount = count; }
    int  GetSunCount() const    { return sunCount; }
    void AddSun(int amount)     { sunCount += amount; }
    bool SpendSun(int amount);

    void SetWaveInfo(int current, int total) { currentWave = current; totalWaves = total; }

    void Render();

private:
    int sunCount;
    int currentWave;
    int totalWaves;
};

#endif // PVZ_HUD_H
