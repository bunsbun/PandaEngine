module;
#include "PandaEngineCore/Log.hpp"
#include <iostream>
#include <memory>

export module application;
import window;
export class Application
{
public:
	Application();
	virtual~Application();

	Application(const Application&) = delete;// Prohibits copying : [X] Application app2 = app1 
	Application(Application&&) = delete;// Prohibits moveing : [X] Application app2 = std::move(app1) 
	Application& operator = (const Application&) = delete;
	Application& operator = (Application&&) = delete;

	virtual int StartApplicationWindow(unsigned int width, unsigned int height, const char* title);
	virtual void OnUpdate() {}; //each frame
	

private:
	std::unique_ptr<Window> m_pWindow;
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
	while (true)
	{
		m_pWindow->OnUpdate();
		OnUpdate();
	}

	return 0;
}

