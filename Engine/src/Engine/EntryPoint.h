#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EG_CORE_WARN("Initialized Log!");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}


#else
#endif // ENGINE_PLATFORM_WINDOWS
