#include "Scene.h"
#include <iostream>
#include "glad.h"

scene* scene::instance()
{
    static scene* sceneInstance = new scene();
    return sceneInstance;
}

scene::scene()
{
    window = nullptr;
    Context = nullptr;
}

bool scene::intialize()
{
    if (SDL_Init(0) == -1)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    window = SDL_CreateWindow("SDL3 OpenGL Window", 1280, 720, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }

    Context = SDL_GL_CreateContext(window);
    if (!Context)
    {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;  // FIXED: Was returning false!
}

void scene::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void scene::swapBuffer()
{
    SDL_GL_SwapWindow(window);
}

void scene::shutdown()
{
    SDL_GL_DestroyContext(Context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}