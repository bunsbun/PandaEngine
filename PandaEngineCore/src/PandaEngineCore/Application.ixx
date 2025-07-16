module;
#include "PandaEngineCore/Log.hpp"  
#include <iostream>  
#include <memory>  
#include <functional>  
#include <PandaEngineCore/Event.hpp>

using namespace PandaEngine;
export module application;
import window;  

export class Application
{
public:
	Application();
	virtual ~Application();

	Application(const Application&) = delete; // Prohibits copying  
	Application(Application&&) = delete; // Prohibits moving  
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	virtual int StartApplicationWindow(unsigned int width, unsigned int height, const char* title);
	virtual void OnUpdate() {}; // each frame  

private:
	std::unique_ptr<Window> m_pWindow;
	EventDispatcher m_eventDispatcher;
	bool m_bCloseWindow = false;
};

Application::Application()
{
	LOG_INFO("Starting Application");
}

Application::~Application()
{
	LOG_INFO("Closing Application");
}

export int Application::StartApplicationWindow(unsigned int width, unsigned int height, const char* title)
{
	m_pWindow = std::make_unique<Window>(title, width, height);

	m_eventDispatcher.AddEventListener<EventMouseMoved>(
		[](EventMouseMoved& event)
		{
			LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
		});

	m_eventDispatcher.AddEventListener<EventWindowResize>(
		[](EventWindowResize& event)
		{
			LOG_INFO("[Resized] Changed size to {0}x{1}", event.height, event.height);
		});

	m_eventDispatcher.AddEventListener<EventWindowClose>(
		[&](EventWindowClose& event)
		{
			LOG_INFO("[WindowClose]");
			m_bCloseWindow = true;
		});


	m_pWindow->SetEventCallback(
		[&](BaseEvent& event)
		{
			m_eventDispatcher.dispatch(event);
		}
	);
	while (!m_bCloseWindow)
	{
		m_pWindow->OnUpdate();
		OnUpdate();
	}
	m_pWindow = nullptr;
	return 0;
}

