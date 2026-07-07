#ifndef PVZ_HUD_H
#define PVZ_HUD_H

class HUD {
public:
    HUD();

    void SetSunCount(int count) { sunCount = count; }
    int  GetSunCount() const    { return sunCount; }
    void AddSun(int amount)     { sunCount += amount; }
    bool SpendSun(int amount);

    void Render();

private:
    int sunCount;
};

#endif // PVZ_HUD_H
