#pragma once
#include <string>

class GLFWwindow;

namespace PandaEngine{

	class Window
	{
	public:
		Window(std::string title, const unsigned int width, const unsigned int height);
		virtual~Window();

		Window(const Window&) = delete;// Prohibits copying : [X] Application app2 = app1 
		Window(Window&&) = delete;// Prohibits moveing : [X] Application app2 = std::move(app1) 
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		virtual void OnUpdate(); //each frame
		unsigned int GetWidthWindow() const { return m_width; };
		unsigned int GetHeightWindow() const { return m_height; };

	private:

		int Init();
		void ShutDown();


		GLFWwindow* m_pWindow;

		std::string m_title = "";

		unsigned int m_width;
		unsigned int m_height;


	};
}