#ifndef BUFFER_H 
#define BUFFER_H
#include "glad.h"

class Buffer
{
public:
    enum class VBOType
    {
        VERTEX,
        INDEX
    };

    Buffer();
    ~Buffer();

    // Create VAO + VBO with vertex count
    void Create(GLsizei vertexCount);

    // Fill VBO with data
    void FillVBO(VBOType type, const void* data, GLsizeiptr size, GLenum usage);

    // Link vertex attribute
    void LinkAttribute(GLuint index,
        GLint componentCount,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const void* offset);

    // Draw
    void DrawArrays(GLenum mode, GLsizei vertexCount);
    void DrawElements(GLenum mode, GLsizei indexCount);

    void Destroy();

private:
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    GLsizei m_vertexCount = 0;
};

#endif // BUFFER_H