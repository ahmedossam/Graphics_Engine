#ifndef INPUT_H 
#define INPUT_H
#include <SDL3/SDL.h>

class Input
{
public:
    static Input* Instance();

public:
    bool IsXClicked();
    bool IsKeyPressed();
    char GetKeyUp();
    char GetKeyDown();
    bool IsLeftButtonClicked();
    bool IsRightButtonClicked();
    bool IsMiddleButtonClicked();
    int GetMousePositionX();
    int GetMousePositionY();
    void Update();

private:
    Input();
    Input(const Input&);
    Input& operator=(const Input&);

private:
    static Input* inputInstance;
    bool xClicked;
    bool keyPressed;
    char keyUp;
    char keyDown;
    bool leftButtonClicked;
    bool rightButtonClicked;
    bool middleButtonClicked;
    int mousePositionX;
    int mousePositionY;
};

#endif