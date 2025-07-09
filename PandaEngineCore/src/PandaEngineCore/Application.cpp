#include "PandaEngineCore/Application.hpp"
#include "PandaEngineCore/Log.hpp"
#include <PandaEngineCore/Window.hpp>
#include <iostream>


namespace PandaEngine
{
	Application::Application()
	{
		LOG_INFO("Starting Application");
	}

	Application::~Application()
	{
		LOG_INFO("Closing Application");
	}

	int Application::StartApplicationWindow(unsigned int width, unsigned int hidth, const char* title)
	{
		m_pWindow = std::make_unique<Window>(title, width, hidth);

		while (true)
		{
			m_pWindow->OnUpdate();
			OnUpdate();
		}

		return 0;
	}
}