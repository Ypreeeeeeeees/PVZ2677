#ifndef PVZ_LAWNMOWER_H
#define PVZ_LAWNMOWER_H

enum class LawnMowerState {
    Idle,
    Moving,
    Gone
};

class LawnMower {
public:
    LawnMower(int row, float x, float y, float speed);

    LawnMower(const LawnMower&) = delete;
    LawnMower& operator=(const LawnMower&) = delete;

    void Update(float dt);
    void Render();
    void Trigger();

    int  GetRow() const           { return row; }
    float GetX() const            { return x; }
    float GetY() const            { return y; }
    LawnMowerState GetState() const { return state; }
    bool IsActive() const         { return state == LawnMowerState::Moving; }

private:
    int row;
    float x, y;
    float speed;
    LawnMowerState state;
    float travelDistance;
};

#endif // PVZ_LAWNMOWER_H
