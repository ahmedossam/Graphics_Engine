#ifndef CAMERA_H
#define CAMERA_H
#include <glm.hpp>
#include"glad.h"

class Camera
{

	public:
	Camera();
	void UpdateViewMatrix();
	void Set3DProjectionMatrix();


private:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_position;
	glm::vec3 m_target;// Look at target
	glm::vec3 m_up;

		
};
#endif

