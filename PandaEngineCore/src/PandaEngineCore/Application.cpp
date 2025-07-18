import application;
#include <iostream>  
#include <memory>  
#include <functional>  
#include <PandaEngineCore/Event.hpp>
#include "PandaEngineCore/Log.hpp"  
using namespace PandaEngine;

int Application::StartApplicationWindow(unsigned int width, unsigned int height, const char* title)
{
	m_pWindow = std::make_unique<Window>(title, width, height);
	LOG_INFO("sadadsasd ");
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