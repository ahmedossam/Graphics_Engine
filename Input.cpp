#include "Input.h"

// Initialize static member
Input* Input::inputInstance = nullptr;

Input::Input()
{
    xClicked = false;
    keyPressed = false;
    keyUp = 0;
    keyDown = 0;
    leftButtonClicked = false;
    rightButtonClicked = false;
    middleButtonClicked = false;
    mousePositionX = 0;
    mousePositionY = 0;
}

Input* Input::Instance()
{
    if (inputInstance == nullptr)
    {
        inputInstance = new Input();
    }
    return inputInstance;
}

bool Input::IsXClicked()
{
    return xClicked;
}

bool Input::IsKeyPressed()
{
    return keyPressed;
}

char Input::GetKeyUp()
{
    return keyUp;
}

char Input::GetKeyDown()
{
    return keyDown;
}

bool Input::IsLeftButtonClicked()
{
    return leftButtonClicked;
}

bool Input::IsRightButtonClicked()
{
    return rightButtonClicked;
}

bool Input::IsMiddleButtonClicked()
{
    return middleButtonClicked;
}

int Input::GetMousePositionX()
{
    return mousePositionX;
}

int Input::GetMousePositionY()
{
    return mousePositionY;
}

void Input::Update()
{
    // Reset per-frame events
    keyUp = 0;
    keyDown = 0;
    keyPressed = false;
    leftButtonClicked = false;
    rightButtonClicked = false;
    middleButtonClicked = false;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            xClicked = true;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            keyPressed = true;
            keyDown = event.key.key;  // SDL3 uses event.key.key instead of keysym.sym
        }
        else if (event.type == SDL_EVENT_KEY_UP)
        {
            keyUp = event.key.key;
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                leftButtonClicked = true;
            else if (event.button.button == SDL_BUTTON_RIGHT)
                rightButtonClicked = true;
            else if (event.button.button == SDL_BUTTON_MIDDLE)
                middleButtonClicked = true;
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
            mousePositionX = (int)event.motion.x;
            mousePositionY = (int)event.motion.y;
        }
    }
}
