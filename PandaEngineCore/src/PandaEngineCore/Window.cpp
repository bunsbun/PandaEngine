#include "PandaEngineCore/Log.hpp"
#include "PandaEngineCore/Event.hpp"  

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

import window;  

static bool s_GLFW_initialized = false;

Window::Window(std::string title, const unsigned int width, const unsigned int height)
	: m_data({ std::move(title), width, height })

{
	int resultCode = Init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true); // keyboard and mouse input enabled
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
	glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);


	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = GetWidthWindow();
	io.DisplaySize.y = GetHeightWindow();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGui::Begin("Background color window");
	ImGui::ColorEdit4("Background color", m_backgroundColor);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();


}