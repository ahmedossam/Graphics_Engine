#include "Buffer.h"
#include "Shader.h"

Buffer::Buffer()
{
    m_EBO = 0;
    m_VBO = 0;
    m_VAO = 0;
    m_vertexCount = 0;
}

Buffer::~Buffer()
{
    Destroy();
}

void Buffer::Create(GLsizei vertexCount)
{
    m_vertexCount = vertexCount;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBindVertexArray(0);
}

void Buffer::FillVBO(VBOType type, const void* data, GLsizeiptr size, GLenum usage)
{
    if (type == VBOType::VERTEX)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else if (type == VBOType::INDEX)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Buffer::LinkAttribute(GLuint index,
    GLint componentCount,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const void* offset)
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(index,
        componentCount,
        type,
        normalized,
        stride,
        offset);

    glEnableVertexAttribArray(index);

    glBindVertexArray(0);
}

void Buffer::DrawArrays(GLenum mode, GLsizei vertexCount)
{
    glBindVertexArray(m_VAO);
    glDrawArrays(mode, 0, vertexCount);
    glBindVertexArray(0);
}

void Buffer::DrawElements(GLenum mode, GLsizei indexCount)
{
    glBindVertexArray(m_VAO);
    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Buffer::Destroy()
{
    if (m_EBO) glDeleteBuffers(1, &m_EBO);
    if (m_VBO) glDeleteBuffers(1, &m_VBO);
    if (m_VAO) glDeleteVertexArrays(1, &m_VAO);

    m_EBO = m_VBO = m_VAO = 0;
}