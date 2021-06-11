#pragma once
namespace Engine
{
	class Event;

	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& evnt) {}
		
		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
