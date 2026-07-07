#ifndef PVZ_BULLET_H
#define PVZ_BULLET_H

class Bullet {
public:
    Bullet(int row, float x, float y, float speed, int damage);

    Bullet(const Bullet&) = delete;
    Bullet& operator=(const Bullet&) = delete;

    void Update(float dt);
    void Render();

    bool IsAlive() const       { return isAlive; }
    bool IsOffScreen() const;
    int  GetRow() const        { return row; }
    float GetX() const         { return x; }
    float GetY() const         { return y; }
    int  GetDamage() const     { return damage; }
    float GetRadius() const    { return radius; }

    void Destroy();

private:
    int row;
    float x, y;
    float speed;
    int damage;
    float radius;
    bool isAlive;
};

#endif // PVZ_BULLET_H
