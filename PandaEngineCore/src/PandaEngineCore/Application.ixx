module;
#include <iostream>  
#include <memory>  
#include <functional>  
#include "PandaEngineCore/Log.hpp" 
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



