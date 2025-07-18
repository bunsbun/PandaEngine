module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

#include "PandaEngineCore/Log.hpp"
#include "PandaEngineCore/Event.hpp"  

using namespace PandaEngine;
export module window;

export class Window
{
public:

	using EventCallbackFn = std::function<void(BaseEvent&)>;

	Window(std::string title, const unsigned int width, const unsigned int height);
	virtual ~Window();

	Window(const Window&) = delete;// Prohibits copying : [X] Application app2 = app1 
	Window(Window&&) = delete;// Prohibits moveing : [X] Application app2 = std::move(app1) 
	Window& operator = (const Window&) = delete;
	Window& operator = (Window&&) = delete;

	virtual void OnUpdate(); //each frame
	unsigned int GetWidthWindow() const { return m_data.m_width; };
	unsigned int GetHeightWindow() const { return m_data.m_height; };

	void SetEventCallback(const EventCallbackFn& callback)
	{
		m_data.m_eventCallback = callback;
	}

private:

	struct WindowData
	{
		std::string m_title = "";
		unsigned int m_width;
		unsigned int m_height;
		EventCallbackFn m_eventCallback;
	};

	int Init();
	void ShutDown();

	GLFWwindow* m_pWindow;
	WindowData m_data;

};

