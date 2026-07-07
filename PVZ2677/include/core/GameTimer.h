#ifndef PVZ_GAMETIMER_H
#define PVZ_GAMETIMER_H

class GameTimer {
public:
    GameTimer();

    float Tick();
    int GetFPS() const { return currentFPS; }

private:
    long long lastTick;
    int frameCount;
    long long fpsTimer;
    int currentFPS;
};

#endif // PVZ_GAMETIMER_H
