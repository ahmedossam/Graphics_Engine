#pragma once
#include "glad.h"
#include "Buffer.h"
#include <glm.hpp>
class Quad
{
public:
    Quad();
    ~Quad();

    void Update();       // Update position based on input
    void Render();       // Render the quad

    void SetPosition(float x, float y);
    void Move(float dx, float dy);

private:
    Buffer m_buffer;
    float m_xPos;
    float m_yPos;
	glm::mat4 m_modelMatrix;// Model transformation matrix
};