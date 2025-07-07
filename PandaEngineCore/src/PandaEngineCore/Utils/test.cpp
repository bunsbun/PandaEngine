#include <iostream>
#include "PandaEngineCore/Utils/test.hpp"
#include <GLFW/glfw3.h>

namespace PandaEngine
{
	int checkGLFW()
	{
		std::cout << "Hello! It's PandaEngineCore!" << std::endl;
		GLFWwindow* window;

		if (!glfwInit())
			return -1;

		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

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
		}

		glfwTerminate();
		return 0;

		return 0;
	}


}
