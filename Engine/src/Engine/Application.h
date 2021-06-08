#pragma once
#include "Core.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
