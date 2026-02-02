#include "Shader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <glm.hpp>

// Static set to track uniforms we've already warned about
static std::set<std::string> warnedUniforms;

Shader* Shader::instance()
{
    static Shader* shader = new Shader;
    return shader;
}


Shader::Shader()
    : m_shaderprogramID(0),
    m_vertexShaderID(0),
    m_fragmentShaderID(0)
{
}

GLuint Shader::getShaderProgramID()
{
    return m_shaderprogramID;
}

bool Shader::CreateProgram()
{
    m_shaderprogramID = glCreateProgram();
    if (m_shaderprogramID == 0)
    {
        std::cout << "ERROR: Failed to create shader program" << std::endl;
        return false;
    }
    return true;
}

bool Shader::CreateShaders()
{
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0)
    {
        std::cout << "ERROR: Failed to create vertex shader" << std::endl;
        return false;
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0)
    {
        std::cout << "ERROR: Failed to create fragment shader" << std::endl;
        return false;
    }
    return true;
}

bool Shader::CompileShaders(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    std::ifstream vFile(vertexPath);
    std::ifstream fFile(fragmentPath);

    if (!vFile || !fFile)
    {
        std::cout << "ERROR: Failed to open shader files" << std::endl;
        std::cout << "  Looking for: " << vertexPath << " and " << fragmentPath << std::endl;
        return false;
    }

    std::stringstream vBuffer, fBuffer;
    vBuffer << vFile.rdbuf();
    fBuffer << fFile.rdbuf();

    vertexShaderCode = vBuffer.str();
    fragmentShaderCode = fBuffer.str();

    const char* vSrc = vertexShaderCode.c_str();
    const char* fSrc = fragmentShaderCode.c_str();

    glShaderSource(m_vertexShaderID, 1, &vSrc, nullptr);
    glCompileShader(m_vertexShaderID);

    glShaderSource(m_fragmentShaderID, 1, &fSrc, nullptr);
    glCompileShader(m_fragmentShaderID);

    GLint success;
    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(m_vertexShaderID, 512, nullptr, log);
        std::cout << "ERROR: Vertex shader compilation failed:\n" << log << std::endl;
        return false;
    }

    glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(m_fragmentShaderID, 512, nullptr, log);
        std::cout << "ERROR: Fragment shader compilation failed:\n" << log << std::endl;
        return false;
    }

    return true;
}

void Shader::AttachShaders()
{
    glAttachShader(m_shaderprogramID, m_vertexShaderID);
    glAttachShader(m_shaderprogramID, m_fragmentShaderID);
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_shaderprogramID);

    GLint success;
    glGetProgramiv(m_shaderprogramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetProgramInfoLog(m_shaderprogramID, 512, nullptr, log);
        std::cout << "ERROR: Shader program linking failed:\n" << log << std::endl;
        return false;
    }

    glUseProgram(m_shaderprogramID);
    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(m_shaderprogramID, m_vertexShaderID);
    glDetachShader(m_shaderprogramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
    glDeleteProgram(m_shaderprogramID);
}

bool Shader::sendUniformData(const std::string& uniformName, GLfloat data)
{
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniform1f(location, data);
    return true;
}

bool Shader::sendUniformData(const std::string& uniformName, GLint data)
{
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniform1i(location, data);
    return true;
}

bool Shader::sendUniformData(const std::string& uniformName, GLuint data)
{
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniform1ui(location, data);
    return true;
}

bool Shader::sendUniformData(const std::string& uniformName, GLfloat x, GLfloat y)
{
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            std::cout << "SOLUTION: Add this line to your Main.vert shader after line 4:" << std::endl;
            std::cout << "  uniform vec2 offset = vec2(0.0, 0.0);" << std::endl;
            std::cout << "And change gl_Position to use the offset." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniform2f(location, x, y);
    return true;
}

bool Shader::sendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z)
{
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniform3f(location, x, y, z);
    return true;
}

bool Shader::sendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniform4f(location, x, y, z, w);
    return true;
}
bool Shader::sendUniformData(const std::string& uniformName, const glm::mat4& matrix)
{
  
    GLint location = glGetUniformLocation(m_shaderprogramID, uniformName.c_str());
    if (location == -1)
    {
        if (warnedUniforms.find(uniformName) == warnedUniforms.end())
        {
            std::cout << "WARNING: Uniform '" << uniformName << "' not found in shader program." << std::endl;
            warnedUniforms.insert(uniformName);
        }
        return false;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	return true;
}

