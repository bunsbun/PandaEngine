module;
#include <string>
#include "PandaEngineCore/Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module window;

export class Window
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

	static bool s_GLFW_initialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		: m_title(std::move(title))
		, m_width(std::move(width))
		, m_height(std::move(height))
	{
		int resultCode = Init();
	}

	Window::~Window()
	{
		ShutDown();
	}

	int Window::Init()
	{
		LOG_INFO("Creating the window {0} width size {1}x{2}!", m_title, m_width, m_height);
		if (!s_GLFW_initialized)
		{
			if (!glfwInit())
			{
				LOG_CRIT("Can't initialize GLFW!");
				return -1;
			}
			s_GLFW_initialized = true;
		}

		m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
		if (!m_pWindow)
		{
			LOG_CRIT("Can't create window {0}!", m_title);
			glfwTerminate();
			return -2;
		}

		glfwMakeContextCurrent(m_pWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_CRIT("Failed to initialize GLAD");
			return -3;
		}
		return 0;
	}

	void Window::ShutDown()
	{
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glClearColor(1, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();

	}