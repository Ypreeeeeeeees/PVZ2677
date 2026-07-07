#ifndef PVZ_CARD_H
#define PVZ_CARD_H

#include <string>

enum class CardType {
    SunFlower,
    PeaShooter,
    WallNut,        // 预留
    Count
};

enum class CardState {
    Normal,         // 可点击
    Cooling,        // 冷却中
    Disabled        // 阳光不足
};

class Card {
public:
    Card();

    void Init(CardType type, const std::wstring& name, int price, float cooldown,
              int x, int y, int w, int h);

    void Update(float dt, int currentSun);
    void Render();

    bool IsClicked(int mx, int my, bool mouseClicked);
    CardType GetType() const { return type; }

    void StartCooldown();

private:
    CardType type;
    std::wstring name;
    int price;
    float cooldown;
    float cooldownTimer;
    CardState state;

    int x, y, width, height;
};

#endif // PVZ_CARD_H
