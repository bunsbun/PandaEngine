#pragma once

#include <memory>
namespace PandaEngine{

	class Application
	{
	public:
		Application();
		virtual~Application();

		Application(const Application&) = delete;// Prohibits copying : [X] Application app2 = app1 
		Application(Application&&) = delete;// Prohibits moveing : [X] Application app2 = std::move(app1) 
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;

		virtual int StartApplicationWindow(unsigned int width, unsigned int hidth, const char* title);
		virtual void OnUpdate(){}; //each frame

	private:
		std::unique_ptr<class Window> m_pWindow;
	};
}