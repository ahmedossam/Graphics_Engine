#include "Quad.h"
#include "Shader.h"
#include "Input.h"
#include "Buffer.h"
#include <iostream>

Quad::Quad()
{
    m_xPos = 0.0f;
    m_yPos = 0.0f;

    Shader* myShader = Shader::instance();

    // Make sure shader program is active
    GLuint programID = myShader->getShaderProgramID();
    std::cout << "Shader Program ID: " << programID << std::endl;
    glUseProgram(programID);

    // Vertex data: position (x,y,z) + color (r,g,b)
    GLfloat vertices[] = {
        // Triangle 1
       -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top-left (Red)
        0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // Top-right (Blue)
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f,  // Bottom-left (Cyan)
       // Triangle 2
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f,  // Bottom-left (Cyan)
       0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // Top-right (Blue)
       0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f   // Bottom-right (Green)
    };

    // Create buffer with 6 vertices
    m_buffer.Create(6);
    m_buffer.FillVBO(Buffer::VBOType::VERTEX, vertices, sizeof(vertices), GL_STATIC_DRAW);

    // Link attributes to shader
    GLuint vertexID = glGetAttribLocation(programID, "vertexIn");
    GLuint colorID = glGetAttribLocation(programID, "colorIn");

    std::cout << "vertexIn location: " << vertexID << std::endl;
    std::cout << "colorIn location: " << colorID << std::endl;

    if (vertexID == -1) {
        std::cout << "ERROR: 'vertexIn' attribute not found in shader!" << std::endl;
    }
    if (colorID == -1) {
        std::cout << "ERROR: 'colorIn' attribute not found in shader!" << std::endl;
    }

    // Position attribute: 3 floats, stride of 6 floats, offset 0
    m_buffer.LinkAttribute(vertexID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

    // Color attribute: 3 floats, stride of 6 floats, offset 3 floats
    m_buffer.LinkAttribute(colorID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // Check uniform location
    GLint offsetLoc = glGetUniformLocation(programID, "offset");
    std::cout << "offset uniform location: " << offsetLoc << std::endl;
    if (offsetLoc == -1) {
        std::cout << "ERROR: 'offset' uniform not found in shader!" << std::endl;
    }
}

Quad::~Quad()
{
    m_buffer.Destroy();
}

void Quad::Update()
{
    Input* input = Input::Instance();

    // Handle WASD movement
    if (input->IsKeyPressed())
    {
        char keyDown = input->GetKeyDown();

        if (keyDown == SDLK_W) m_yPos += 0.01f;
        if (keyDown == SDLK_S) m_yPos -= 0.01f;
        if (keyDown == SDLK_A) m_xPos -= 0.01f;
        if (keyDown == SDLK_D) m_xPos += 0.01f;
    }
}

void Quad::Render()
{
    Shader* myShader = Shader::instance();

    // Make sure shader is active before sending uniforms
    glUseProgram(myShader->getShaderProgramID());

    // Send position to shader as uniform
    myShader->sendUniformData("offset", m_xPos, m_yPos);

    // Draw the quad
    m_buffer.DrawArrays(GL_TRIANGLES, 6);
}

void Quad::SetPosition(float x, float y)
{
    m_xPos = x;
    m_yPos = y;
}

void Quad::Move(float dx, float dy)
{
    m_xPos += dx;
    m_yPos += dy;
}