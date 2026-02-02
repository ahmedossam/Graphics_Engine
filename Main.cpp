#include "glad.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <iostream>
#include "Scene.h"
#include "Input.h"
#include "Shader.h"
#include "Quad.h"
#include<glm.hpp>
#include"Camera.h"
int main(int argc, char* argv[])
{
    // ----- Initialize Scene -----
    scene* myScene = scene::instance();
    if (!myScene->intialize()) {
        std::cout << "Failed to initialize scene." << std::endl;
        return -1;
    }

    // ----- Initialize Shader -----
    Shader* myShader = Shader::instance();
    myShader->CreateProgram();
    myShader->CreateShaders();
    myShader->CompileShaders("Shaders/Main.vert", "Shaders/Main.frag");
    myShader->AttachShaders();
    myShader->LinkProgram();

    // ----- Create Quad -----
    Quad* myQuad = new Quad();
	Camera myCamera;

    bool isActive = true;
    Input* input = Input::Instance();
    myCamera.Set3DProjectionMatrix();

    // ----- Main loop -----
    while (isActive)
    {
        // ----- Update input -----
        input->Update();
        isActive = !input->IsXClicked();
        
        // ----- Clear screen -----
        myScene->clearScreen();
		
		myCamera.UpdateViewMatrix();
        // Update quad position based on input
        myQuad->Update();
        
         // ----- Render quad (sends uniforms internally) -----
        myQuad->Render();
		
        // ----- Swap buffers -----
        myScene->swapBuffer();
    }

    // ----- Cleanup -----
    delete myQuad;
    myShader->DetachShaders();
    myShader->DestroyShaders();
    myShader->DestroyProgram();
    myScene->shutdown();

    return 0;
}