#include "core/GameTimer.h"
#include <chrono>

GameTimer::GameTimer()
    : lastTick(0), frameCount(0), fpsTimer(0), currentFPS(0) {
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    lastTick = ms;
    fpsTimer = ms;
}

float GameTimer::Tick() {
    auto now = std::chrono::steady_clock::now();
    long long currentMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();

    long long elapsed = currentMs - lastTick;
    lastTick = currentMs;

    float dt = static_cast<float>(elapsed) / 1000.0f;
    if (dt > 0.1f) {
        dt = 0.1f;
    }

    frameCount++;
    if (currentMs - fpsTimer >= 1000) {
        currentFPS = frameCount;
        frameCount = 0;
        fpsTimer = currentMs;
    }

    return dt;
}
