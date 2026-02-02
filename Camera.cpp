#include "Camera.h"
#include <gtc/matrix_transform.hpp>
#include"Shader.h"
#include"Input.h"
Camera::Camera()
{
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);


	m_position = glm::vec3(0.0f);
	m_target = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}
void Camera::UpdateViewMatrix()
{
    Input* input = Input::Instance();

    if (input->IsKeyPressed())
    {
        char keyDown = input->GetKeyDown();

		// Movement (Z for zoom )//c and X for out // C and V for left and right
		if (keyDown == SDLK_Z) m_position.z += 0.1f;  // ZOOM IN
		if (keyDown == SDLK_X) m_position.z -= 0.1f;  // ZOOM OUT
		if (keyDown == SDLK_C) m_position.x -= 0.1f;  // LEFT
		if (keyDown == SDLK_V) m_position.x += 0.1f;  // RIGHT
		



        m_viewMatrix = glm::lookAt(m_position, m_position + m_target, m_up);
        Shader::instance()->sendUniformData("view", m_viewMatrix);

    }

}

void Camera::Set3DProjectionMatrix()
{
	constexpr float fov = 45.0f;
	float aspectRatio = 800.0f / 600.0f; // Assuming a window size of 800x600
	float nearPlane = 0.001f;
	float farPlane = 1000.0f;
	m_projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	Shader::instance()->sendUniformData("projection", m_projectionMatrix);
}
