#ifndef Scene_h
#define Scene_h
#include <SDL3/SDL.h>

class scene
{
public:
    static scene* instance();

public:
    bool intialize();
    void clearScreen();
    void swapBuffer();
    void shutdown();

private:
    scene();
    scene(const scene&);
    scene& operator=(const scene&);

private:
    SDL_Window* window = nullptr;
    SDL_GLContext Context = nullptr;
};

#endif

