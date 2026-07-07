#ifndef PVZ_BUTTON_H
#define PVZ_BUTTON_H

#include <string>
#include <graphics.h>

enum class ButtonState {
    Normal,
    Hover,
    Pressed
};

class Button {
public:
    Button() = default;

    void Init(int x, int y, int w, int h, const std::wstring& label,
              COLORREF colorNormal, COLORREF colorHover, COLORREF colorText);
    void Update(int mouseX, int mouseY, bool mouseDown, bool mouseClicked);
    void Render();

    bool IsHovered() const { return state == ButtonState::Hover; }
    bool IsClicked() const { return clicked; }
    void SetEnabled(bool enabled) { this->enabled = enabled; }
    bool IsEnabled() const { return enabled; }

private:
    int x = 0, y = 0, width = 0, height = 0;
    std::wstring text;
    COLORREF colorNormal = 0;
    COLORREF colorHover = 0;
    COLORREF colorText = 0;
    ButtonState state = ButtonState::Normal;
    bool clicked = false;
    bool enabled = true;
};

#endif // PVZ_BUTTON_H
