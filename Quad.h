#pragma once
#include "glad.h"
#include "Buffer.h"
#include <glm.hpp>


class Quad
{
public:
    Quad();
    ~Quad();

    void Update();       // Update transformation based on input
    void Render();       // Render the quad

    void SetPosition(float x, float y);
    void SetScale(float x, float y);
    void SetRotation(float angle);
    void Move(float dx, float dy);

private:
    Buffer m_buffer;

    glm::vec3 m_position;    // Position (x, y, z)
    glm::vec3 m_scale;       // Scale (x, y, z)
    float m_rotation;        // Rotation angle in radians

    glm::mat4 m_modelMatrix; // Combined transformation matrix
};