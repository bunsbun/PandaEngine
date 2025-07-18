#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "PandaEngineCore/Log.hpp"
#include "PandaEngineCore/Event.hpp"  

import window;  

static bool s_GLFW_initialized = false;

Window::Window(std::string title, const unsigned int width, const unsigned int height)
	: m_data({ std::move(title), width, height })

{
	int resultCode = Init();
}

Window::~Window()
{
	ShutDown();
}

int Window::Init()
{
	LOG_INFO("Creating the window {0} width size {1}x{2}!", m_data.m_title, m_data.m_width, m_data.m_height);
	if (!s_GLFW_initialized)
	{
		if (!glfwInit())
		{
			LOG_CRIT("Can't initialize GLFW!");
			return -1;
		}
		s_GLFW_initialized = true;
	}

	m_pWindow = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
	if (!m_pWindow)
	{
		LOG_CRIT("Can't create window {0}!", m_data.m_title);
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(m_pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_CRIT("Failed to initialize GLAD");
		return -3;
	}

	glfwSetWindowUserPointer(m_pWindow, &m_data);

	glfwSetWindowSizeCallback(m_pWindow,
		[](GLFWwindow* pWindow, int width, int height)
		{
			LOG_INFO("New size {0}x{1}", width, height);
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
			data.m_width = width;
			data.m_height = height;

			PandaEngine::EventWindowResize event(width, height);
			data.m_eventCallback(event);

		}
	);

	glfwSetCursorPosCallback(m_pWindow,
		[](GLFWwindow* pWindow, double x, double y)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			PandaEngine::EventMouseMoved event(x, y);
			data.m_eventCallback(event);
		}
	);

	glfwSetWindowCloseCallback(m_pWindow,
		[](GLFWwindow* pWindow)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			PandaEngine::EventWindowClose event;
			data.m_eventCallback(event);
		}
	);

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