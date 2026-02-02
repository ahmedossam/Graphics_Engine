#include "Quad.h"
#include "Shader.h"
#include "Input.h"
#include "Buffer.h"
#include <iostream>
#include <gtc/matrix_transform.hpp>

Quad::Quad()
{
    // Initialize transformation variables properly
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_scale = glm::vec3(1.0f, 1.0f, 1.0f);    // Start with normal scale (1.0)
    m_rotation = 0.0f;
    m_modelMatrix = glm::mat4(1.0f);

    Shader* myShader = Shader::instance();
    GLuint programID = myShader->getShaderProgramID();
     
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

    m_buffer.Create(6);
    m_buffer.FillVBO(Buffer::VBOType::VERTEX, vertices, sizeof(vertices), GL_STATIC_DRAW);

    GLuint vertexID = glGetAttribLocation(programID, "vertexIn");
    GLuint colorID = glGetAttribLocation(programID, "colorIn");

    m_buffer.LinkAttribute(vertexID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    m_buffer.LinkAttribute(colorID, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

Quad::~Quad()
{
    m_buffer.Destroy();
}

void Quad::Update()
{
    Input* input = Input::Instance();

    if (input->IsKeyPressed())
    {
        char keyDown = input->GetKeyDown();

        // Movement (WASD)
        if (keyDown == SDLK_W) m_position.y += 0.01f;  // UP
        if (keyDown == SDLK_S) m_position.y -= 0.01f;  // DOWN
        if (keyDown == SDLK_A) m_position.x -= 0.01f;  // LEFT
        if (keyDown == SDLK_D) m_position.x += 0.01f;  // RIGHT

        // Scaling (Q to grow, E to shrink)
        if (keyDown == SDLK_Q) {
            m_scale.x += 0.01f;
            m_scale.y += 0.01f;
        }
        if (keyDown == SDLK_E) {
            m_scale.x -= 0.01f;
            m_scale.y -= 0.01f;
            if (m_scale.x < 0.1f) m_scale.x = 0.1f;
            if (m_scale.y < 0.1f) m_scale.y = 0.1f;
        }

        // Rotation (R clockwise, F counter-clockwise)
        if (keyDown == SDLK_R) m_rotation += 0.05f;   // ~2.86 degrees
        if (keyDown == SDLK_F) m_rotation -= 0.05f;   // ~2.86 degrees
    }

    // Build model matrix: Translate × Rotate × Scale
    m_modelMatrix = glm::mat4(1.0f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_position);
    m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
}

void Quad::Render()
{
    Shader* myShader = Shader::instance();
    glUseProgram(myShader->getShaderProgramID());

    // Send model matrix to shader
    GLuint modelLoc = glGetUniformLocation(myShader->getShaderProgramID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

    m_buffer.DrawArrays(GL_TRIANGLES, 6);
}

void Quad::SetPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void Quad::SetScale(float x, float y)
{
    m_scale.x = x;
    m_scale.y = y;
}

void Quad::SetRotation(float angle)
{
    m_rotation = angle;
}

void Quad::Move(float dx, float dy)
{
    m_position.x += dx;
    m_position.y += dy;
}