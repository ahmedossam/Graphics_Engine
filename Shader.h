#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "glad.h"
#include<glm.hpp>

class Shader
{
public:
    static Shader* instance();

public:
    GLuint getShaderProgramID();

    bool CreateProgram();
    bool CreateShaders();

    bool CompileShaders(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    void AttachShaders();
    bool LinkProgram();

    void DetachShaders();
    void DestroyShaders();
    void DestroyProgram();

    bool sendUniformData(const std::string& uniformName, GLfloat data);
    bool sendUniformData(const std::string& uniformName, GLint data);
    bool sendUniformData(const std::string& uniformName, GLuint data);

    bool sendUniformData(const std::string& uniformName, GLfloat x, GLfloat y);
    bool sendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z);
    bool sendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	// Add matrix uniform sender
	
	bool sendUniformData(const std::string& uniformName, const glm::mat4& matrix);
private:
    Shader();
    Shader(const Shader&);
    Shader& operator=(const Shader&);

private:
    GLuint m_shaderprogramID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};

#endif // SHADER_H