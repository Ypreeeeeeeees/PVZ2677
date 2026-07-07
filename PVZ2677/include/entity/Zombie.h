#ifndef PVZ_ZOMBIE_H
#define PVZ_ZOMBIE_H

#include <string>

enum class ZombieState {
    Walking,
    Attacking,
    Dead
};

class Zombie {
public:
    Zombie(const std::wstring& name, int row, float x, float y,
           int health, int maxHealth, float speed, int attackPower,
           float attackInterval);
    virtual ~Zombie() = default;

    Zombie(const Zombie&) = delete;
    Zombie& operator=(const Zombie&) = delete;

    virtual void Update(float dt);
    virtual void Render();
    virtual void TakeDamage(int damage);

    void SetTargetPlantAlive(bool alive) { targetPlantAlive = alive; }

    // ---- Getter ----
    float       GetX() const             { return x; }
    float       GetY() const             { return y; }
    int         GetRow() const           { return row; }
    int         GetHealth() const        { return health; }
    int         GetMaxHealth() const     { return maxHealth; }
    float       GetSpeed() const         { return speed; }
    int         GetAttackPower() const   { return attackPower; }
    bool        IsAlive() const          { return isAlive; }
    bool        IsAttacking() const      { return state == ZombieState::Attacking; }
    bool        HasReachedEnd() const    { return reachedEnd; }
    ZombieState GetState() const         { return state; }
    const std::wstring& GetName() const  { return name; }

protected:
    std::wstring name;
    int row;
    float x, y;
    int health;
    int maxHealth;
    float speed;
    int attackPower;
    float attackInterval;
    float attackTimer;
    bool isAlive;
    bool reachedEnd;
    bool targetPlantAlive;
    ZombieState state;
    float deathTimer;
};

#endif // PVZ_ZOMBIE_H
