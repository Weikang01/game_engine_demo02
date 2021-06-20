#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(const float radiance) { m_Rotation = radiance; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_Project; }
		const glm::mat4& GetViewMatrix() const { return m_View; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_Project;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		glm::vec3 m_Position = glm::vec3(0.f);
		float m_Rotation = 0.f;
	};
}
