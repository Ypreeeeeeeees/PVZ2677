#include "system/InputManager.h"
#include <graphics.h>
#include <windows.h>

InputManager::InputManager()
    : mouseX(0), mouseY(0), mouseDown(false),
      mouseClicked(false), prevMouseDown(false) {
    for (int i = 0; i < 256; i++) {
        keyDown[i] = false;
        prevKeyDown[i] = false;
    }
}

void InputManager::Update() {
    ExMessage msg;
    while (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
        if (msg.message == WM_MOUSEMOVE || msg.message == WM_LBUTTONDOWN ||
            msg.message == WM_LBUTTONUP) {
            mouseX = msg.x;
            mouseY = msg.y;
            prevMouseDown = mouseDown;
            mouseDown = msg.lbutton;
        } else if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP) {
            prevKeyDown[msg.vkcode] = keyDown[msg.vkcode];
            keyDown[msg.vkcode] = (msg.message == WM_KEYDOWN);
        }
    }
    mouseClicked = (!mouseDown) && prevMouseDown;
}

bool InputManager::IsKeyPressed(int key) const {
    return keyDown[key] && !prevKeyDown[key];
}

bool InputManager::IsKeyDown(int key) const {
    return keyDown[key];
}
