#pragma once
#include "OrthographicCamera.h"
#include "Engine/Core/Timestep.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		const OrthographicCamera& getCamera() const { return m_camera; }
		OrthographicCamera& getCamera() { return m_camera; }
	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	private:
		float m_aspectRatio;
		float m_zoomLevel = 1.f;
		OrthographicCamera m_camera;
		glm::vec3 m_camPos = { 0.f,0.f ,0.f };
		float m_camSpeed = .1f;
		float m_camAngle = 0.f;
		float m_camRotSpeed = 1.f;
		bool m_rotation;
	};
}
