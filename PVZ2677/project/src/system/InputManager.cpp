#include "system/InputManager.h"
#include <graphics.h>
#include <windows.h>

InputManager::InputManager()
    : mouseX(0), mouseY(0), mouseDown(false),
      mouseClicked(false) {
    for (int i = 0; i < 256; i++) {
        keyDown[i] = false;
        keyPressed[i] = false;
    }
}

void InputManager::Update() {
    // 重置每帧状态
    mouseClicked = false;
    for (int i = 0; i < 256; i++) {
        keyPressed[i] = false;
    }

    ExMessage msg;
    while (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
        if (msg.message == WM_MOUSEMOVE || msg.message == WM_LBUTTONDOWN ||
            msg.message == WM_LBUTTONUP) {
            mouseX = msg.x;
            mouseY = msg.y;
            bool wasDown = mouseDown;
            mouseDown = msg.lbutton;
            // 仅在消息循环内检测上升沿，杜绝跨帧残留
            if (!mouseDown && wasDown) {
                mouseClicked = true;
            }
        } else if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP) {
            if (msg.message == WM_KEYDOWN && !keyDown[msg.vkcode]) {
                keyPressed[msg.vkcode] = true;
            }
            keyDown[msg.vkcode] = (msg.message == WM_KEYDOWN);
        }
    }
}

bool InputManager::IsKeyPressed(int key) const {
    return keyPressed[key];
}

bool InputManager::IsKeyDown(int key) const {
    return keyDown[key];
}
