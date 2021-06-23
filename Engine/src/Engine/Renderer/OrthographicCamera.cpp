#include "engine_pch.h"
#include "OrthographicCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_Project(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_View(1.f)
	{
		m_ViewProjection = m_Project * m_View;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_Project = glm::ortho(left, right, bottom, top, -1.f, 1.f);
		m_ViewProjection = m_Project * m_View;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(0.f, 0.f, 1.f));
		m_View = glm::inverse(transform);
		m_ViewProjection = m_Project * m_View;
	}
}