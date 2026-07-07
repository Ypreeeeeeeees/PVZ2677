#include "entity/Bullet.h"
#include "utils/Constants.h"
#include <graphics.h>

Bullet::Bullet(int row, float x, float y, float speed, int damage)
    : row(row), x(x), y(y), speed(speed), damage(damage),
      radius(10.0f), isAlive(true) {
}

void Bullet::Update(float dt) {
    if (!isAlive) return;
    x += speed * dt;
    if (IsOffScreen()) {
        isAlive = false;
    }
}

void Bullet::Render() {
    if (!isAlive) return;

    int drawX = static_cast<int>(x);
    int drawY = static_cast<int>(y);

    // 豌豆占位：绿色实心圆
    setfillcolor(RGB(100, 220, 80));
    solidcircle(drawX, drawY, static_cast<int>(radius));
}

bool Bullet::IsOffScreen() const {
    return x > GameConstants::WINDOW_WIDTH + 20;
}

void Bullet::Destroy() {
    isAlive = false;
}
