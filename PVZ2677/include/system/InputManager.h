#ifndef PVZ_INPUTMANAGER_H
#define PVZ_INPUTMANAGER_H

class InputManager {
public:
    InputManager();

    void Update();

    int GetMouseX() const { return mouseX; }
    int GetMouseY() const { return mouseY; }
    bool IsMouseClicked() const { return mouseClicked; }
    bool IsMouseDown() const { return mouseDown; }
    bool IsKeyPressed(int key) const;
    bool IsKeyDown(int key) const;

private:
    int  mouseX, mouseY;
    bool mouseDown;
    bool mouseClicked;
    bool prevMouseDown;
    bool keyDown[256];
    bool prevKeyDown[256];
};

#endif // PVZ_INPUTMANAGER_H
