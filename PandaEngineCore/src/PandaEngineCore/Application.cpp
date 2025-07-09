
#include "PandaEngineCore/Application.hpp"
#include "PandaEngineCore/Log.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

namespace PandaEngine
{
	Application::Application()
	{
		std::cout << "Application CONSTRUCTOR!" << std::endl;
		LOG_INFO("Welcome to spdlog!");
		LOG_ERROR("Some error message with arg: {}", 1);

		LOG_WARN("Easy padding in numbers like {:08d}", 12);
		LOG_CRIT("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
;

		//spdlog::set_level(spdlog::level::debug); // Set global log level to debug
		//spdlog::debug("This message should be displayed..");

		//// change log pattern
		//spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

		// Compile time log levels
		// Note that this does not change the current log level, it will only
		// remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
		SPDLOG_TRACE("Some trace message with param {}", 42);
		SPDLOG_DEBUG("Some debug message");
	}

	Application::~Application()
	{
		std::cout << "Application DiSTRUCTOR!" << std::endl;
	}

	//consteval
	
	static int y = 0;
	int Application::StartApplicationWindow(unsigned int width, unsigned int hidth, const char* title)
	{
		std::cout << "Hello! It's PandaEngineCore!" << std::endl;
		GLFWwindow* window;

		if (!glfwInit())
		{
			return -1;
		}


		window = glfwCreateWindow(width, hidth, title, NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);

		while (!glfwWindowShouldClose(window))
		{
			//glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

			OnUpdate();
		}

		glfwTerminate();
		return 0;
	}
}