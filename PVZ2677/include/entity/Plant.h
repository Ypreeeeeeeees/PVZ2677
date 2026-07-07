#ifndef PVZ_PLANT_H
#define PVZ_PLANT_H

#include <string>

enum class PlantState {
    Planting,
    Idle,
    Attacking,
    Dead
};

class Plant {
public:
    Plant(const std::wstring& name, int row, int col,
          int health, int maxHealth, int price, float cooldown,
          float attackSpeed);
    virtual ~Plant() = default;

    Plant(const Plant&) = delete;
    Plant& operator=(const Plant&) = delete;

    virtual void Update(float dt);
    virtual void Render();
    virtual void TakeDamage(int damage);

    // ---- Getter ----
    int               GetRow() const          { return row; }
    int               GetCol() const          { return col; }
    int               GetHealth() const       { return health; }
    int               GetMaxHealth() const    { return maxHealth; }
    int               GetPrice() const        { return price; }
    float             GetCooldown() const     { return cooldown; }
    float             GetAttackSpeed() const  { return attackSpeed; }
    bool              IsAlive() const         { return isAlive; }
    const std::wstring& GetName() const       { return name; }
    PlantState        GetState() const        { return state; }

protected:
    std::wstring name;
    int row, col;
    int health;
    int maxHealth;
    int price;
    float cooldown;
    float attackSpeed;
    bool isAlive;
    PlantState state;
    float plantTimer;          // 种植动画计时器（Planting → Idle）
    float deathTimer;          // 死亡动画计时器
};

#endif // PVZ_PLANT_H
