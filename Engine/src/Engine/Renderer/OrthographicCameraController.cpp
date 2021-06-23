#include "engine_pch.h"
#include "OrthographicCameraController.h"
#include "Engine/Input.h"
#include "Engine/Events/KeyEvent.h"

namespace Engine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation), m_camSpeed(m_zoomLevel)
	{
	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::A))
			m_camPos.x -= m_camSpeed * ts;

		if (Input::IsKeyPressed(Key::D))
			m_camPos.x += m_camSpeed * ts;

		if (Input::IsKeyPressed(Key::S))
			m_camPos.y -= m_camSpeed * ts;

		if (Input::IsKeyPressed(Key::W))
			m_camPos.y += m_camSpeed * ts;

		if (Input::IsKeyPressed(Key::Q))
			m_camAngle += m_camRotSpeed * ts * m_rotation;

		if (Input::IsKeyPressed(Key::E))
			m_camAngle -= m_camRotSpeed * ts * m_rotation;

		m_camera.SetPosition(m_camPos);
		if (m_camAngle)
			m_camera.SetRotation(m_camAngle);
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		float transmission = std::max(std::min(m_zoomLevel * m_zoomLevel, 3.f), 0.02f);
		m_zoomLevel -= e.GetYOffset() * transmission * .2f;
		std::cout << m_zoomLevel << "  "<< e.GetYOffset() << std::endl;
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

		m_camSpeed = m_zoomLevel;
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}
}