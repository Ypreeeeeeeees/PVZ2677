#include "component/Button.h"

void Button::Init(int x, int y, int w, int h, const std::wstring& label,
                  COLORREF colorNormal, COLORREF colorHover, COLORREF colorText) {
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->text = label;
    this->colorNormal = colorNormal;
    this->colorHover = colorHover;
    this->colorText = colorText;
    this->state = ButtonState::Normal;
    this->clicked = false;
    this->enabled = true;
}

void Button::Update(int mouseX, int mouseY, bool mouseDown, bool mouseClicked) {
    if (!enabled) {
        state = ButtonState::Normal;
        clicked = false;
        return;
    }

    bool inside = (mouseX >= x && mouseX <= x + width &&
                   mouseY >= y && mouseY <= y + height);

    clicked = false;

    if (inside) {
        if (mouseDown) {
            state = ButtonState::Pressed;
        } else {
            state = ButtonState::Hover;
        }
        if (mouseClicked) {
            clicked = true;
        }
    } else {
        state = ButtonState::Normal;
    }
}

void Button::Render() {
    COLORREF bgColor = (state == ButtonState::Hover || state == ButtonState::Pressed)
                       ? colorHover : colorNormal;

    setfillcolor(bgColor);
    solidroundrect(x, y, x + width, y + height, 8, 8);

    setbkmode(TRANSPARENT);
    settextcolor(colorText);
    settextstyle(24, 0, _T("微软雅黑"));

    int textWidth = textwidth(text.c_str());
    int textHeight = textheight(text.c_str());
    int tx = x + (width - textWidth) / 2;
    int ty = y + (height - textHeight) / 2;
    outtextxy(tx, ty, text.c_str());
}
