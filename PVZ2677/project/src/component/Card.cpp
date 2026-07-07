#include "component/Card.h"
#include "utils/Constants.h"
#include <graphics.h>

Card::Card()
    : type(CardType::SunFlower), price(0), cooldown(0.0f),
      cooldownTimer(0.0f), state(CardState::Normal),
      x(0), y(0), width(60), height(70) {
}

void Card::Init(CardType type, const std::wstring& name, int price, float cooldown,
                int x, int y, int w, int h) {
    this->type = type;
    this->name = name;
    this->price = price;
    this->cooldown = cooldown;
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->cooldownTimer = 0.0f;
    this->state = CardState::Normal;
}

void Card::Update(float dt, int currentSun) {
    if (state == CardState::Cooling) {
        cooldownTimer += dt;
        if (cooldownTimer >= cooldown) {
            cooldownTimer = 0.0f;
        }
    }

    if (cooldownTimer > 0.0f) {
        state = CardState::Cooling;
    } else if (currentSun < price) {
        state = CardState::Disabled;
    } else {
        state = CardState::Normal;
    }
}

bool Card::IsClicked(int mx, int my, bool mouseClicked) {
    if (state != CardState::Normal) return false;
    if (!mouseClicked) return false;

    return (mx >= x && mx <= x + width &&
            my >= y && my <= y + height);
}

void Card::StartCooldown() {
    cooldownTimer = 0.001f; // 开始计时
    state = CardState::Cooling;
}

void Card::Render() {
    COLORREF bg;
    int border;

    switch (state) {
    case CardState::Normal:
        bg = RGB(70, 130, 50);
        border = 2;
        break;
    case CardState::Cooling:
        bg = RGB(50, 50, 50);
        border = 1;
        break;
    case CardState::Disabled:
        bg = RGB(40, 40, 40);
        border = 1;
        break;
    }

    // 卡片背景
    setfillcolor(bg);
    solidroundrect(x, y, x + width, y + height, 4, 4);

    // 边框
    setlinecolor(RGB(120, 100, 60));
    setlinestyle(PS_SOLID, border);
    rectangle(x, y, x + width, y + height);

    // 冷却遮罩
    if (state == CardState::Cooling && cooldown > 0.0f) {
        float ratio = cooldownTimer / cooldown;
        int maskH = static_cast<int>(height * (1.0f - ratio));
        setfillcolor(RGB(50, 50, 50));
        solidrectangle(x, y, x + width, y + maskH);
    }

    // 价格
    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 255, 200));
    settextstyle(14, 0, _T("微软雅黑"));
    std::wstring priceStr = std::to_wstring(price);
    int pw = textwidth(priceStr.c_str());
    outtextxy(x + 5, y + height - 22, priceStr.c_str());

    // 名称
    settextcolor(RGB(255, 255, 255));
    settextstyle(11, 0, _T("微软雅黑"));
    int nw = textwidth(name.c_str());
    outtextxy(x + (width - nw) / 2, y + 5, name.c_str());
}
