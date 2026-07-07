#ifndef PVZ_SUN_H
#define PVZ_SUN_H

enum class SunState {
    Spawning,
    Floating,
    Collected,
    Vanished
};

class Sun {
public:
    Sun(float x, float y, int value);

    Sun(const Sun&) = delete;
    Sun& operator=(const Sun&) = delete;

    void Update(float dt);
    void Render();

    int      GetValue() const    { return value; }
    float    GetX() const        { return x; }
    float    GetY() const        { return y; }
    SunState GetState() const    { return state; }
    bool     IsAlive() const     { return state != SunState::Vanished; }
    bool     IsCollectible() const { return state == SunState::Floating; }

    void Collect();              // 玩家点击收集
    void SetFalling(bool fall) { isFalling = fall; }
    void SetTargetY(float ty)  { targetY = ty; }

private:
    float x, y;
    float targetY;               // 自然阳光飘落的目标 Y
    int value;
    SunState state;
    bool isFalling;              // 自然阳光从天空飘落
    float timer;
    float spawnTimer;
    float vanishTimer;
};

#endif // PVZ_SUN_H
